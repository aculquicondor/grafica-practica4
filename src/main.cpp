#include <iostream>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "scene.h"
#include "perspective_camera.h"
#include "uniform_color.h"
#include "rectangle.h"
#include "data_buffer_2.h"


using namespace std;


PerspectiveCamera *camera;
float cam_dist = 15;
MvpProgram *program = nullptr;

class Center : public Drawable {
public:
    Center() : Drawable(nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr, nullptr), position(0, 0, 0), angle_z(0) {}

    glm::vec3 position;
    float angle_z;
    virtual glm::mat4 get_model(float time) {
        return Drawable::get_model(time) *
                glm::rotate(-angle_z, glm::vec3(0, 1, 0)) * glm::translate(position);
    }

    void move_horizontal(float d) {
        position += glm::rotateY(glm::vec3(d, 0, 0), angle_z);
    }

    void move_vertical(float d) {
        position -= glm::rotateY(glm::vec3(0, 0, d), angle_z);
    }
};


Center *center;


void scroll(GLFWwindow* window, double x_offset, double y_offset) {
    center->angle_z -= x_offset * .02;
    cam_dist -= y_offset * .1;
    camera->look_at(glm::vec3(0, cam_dist *.6f, cam_dist), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}


class Floor : public Drawable {
public:
    Floor(Drawable *parent = nullptr) :
            Drawable(::program,
                     new Rectangle(glm::vec3(-20, 0, -20), glm::vec3(-20, 0, 20), glm::vec3(20, 0, -20)),
                     GL_TRIANGLE_STRIP, new UniformColor({.1f, .2f, .1f, 1.f}, 4), new Texture("textures/grass.jpg", GL_BGR),
                     new DataBuffer2({{8, 0}, {0, 0}, {0, 8}, {8, 8}}, 2),
                     new DataBuffer3({{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}}, 3), parent) { }
};


class House : public Drawable {
private:
    Drawable *parts[8];
    Texture *wall_texture, *roof_texture;
public:
    House(Drawable *parent = nullptr) : Drawable(::program, nullptr, 0, nullptr, nullptr, nullptr, nullptr, parent) {
        UniformColor *roof_color = new UniformColor({.3, .3, .8, 1}, 4),
                *wall_color = new UniformColor({.2, 0., 0., 1.}, 4);
        wall_texture = new Texture("textures/wall.jpg", GL_BGR);
        roof_texture = new Texture("textures/roof.jpg", GL_BGR);
        // walls
        parts[0] = new Drawable(::program, new Rectangle({4, 0, -3}, {4, 2, -3}, {4, 0, 3}), GL_TRIANGLE_STRIP,
                                wall_color, wall_texture,
                                new DataBuffer2({{0, 2}, {0, 0}, {3, 2}, {3, 0}}, 2),
                                new DataBuffer3({{1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}}, 3), parent);
        parts[1] = new Drawable(::program, new Rectangle({-4, 0, -3}, {-4, 2, -3}, {-4, 0, 3}), GL_TRIANGLE_STRIP,
                                wall_color, wall_texture,
                                new DataBuffer2({{0, 2}, {0, 0}, {3, 2}, {3, 0}}, 2),
                                new DataBuffer3({{-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}}, 3), parent);
        parts[2] = new Drawable(::program, new Rectangle({-4, 0, -3}, {-4, 2, -3}, {4, 0, -3}), GL_TRIANGLE_STRIP,
                                wall_color, wall_texture,
                                new DataBuffer2({{0, 2}, {0, 0}, {4, 2}, {4, 0}}, 2),
                                new DataBuffer3({{0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1}}, 3), parent);
        parts[3] = new Drawable(::program, new Rectangle({-4, 0, 3}, {-4, 2, 3}, {4, 0, 3}), GL_TRIANGLE_STRIP,
                                wall_color, wall_texture,
                                new DataBuffer2({{0, 2}, {0, 0}, {4, 2}, {4, 0}}, 2),
                                new DataBuffer3({{0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}}, 3), parent);
        parts[4] = new Drawable(::program, new DataBuffer3({{-4, 2, -3}, {-4, 2,  3}, {-4, 3, 0}}), GL_TRIANGLE_STRIP,
                                wall_color, wall_texture,
                                new DataBuffer2({{0, 0}, {3, 0}, {1.5, 1}}, 2),
                                new DataBuffer3({{-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}}, 3), parent);
        parts[5] = new Drawable(::program, new DataBuffer3({{4, 2, -3}, {4, 2, 3}, {4, 3, 0}}), GL_TRIANGLE_STRIP,
                                wall_color, wall_texture,
                                new DataBuffer2({{0, 0}, {3, 0}, {1.5, 1}}, 2),
                                new DataBuffer3({{1, 0, 0}, {1, 0, 0}, {1, 0, 0}}, 3), parent);
        // ceiling
        glm::vec3 norm1(0, 3, -1), norm2(0, 3, 1);
        parts[6] = new Drawable(::program, new Rectangle({-4, 2, -3}, {-4, 3, 0}, {4, 2, -3}), GL_TRIANGLE_STRIP,
                                roof_color, roof_texture,
                                new DataBuffer2({{0, 2}, {0, 0}, {4, 2}, {4, 0}}, 2),
                                new DataBuffer3({norm1, norm1, norm1, norm1}, 3), parent);
        parts[7] = new Drawable(::program, new Rectangle({-4, 2, 3}, {-4, 3, 0}, {4, 2, 3}), GL_TRIANGLE_STRIP,
                                roof_color, roof_texture,
                                new DataBuffer2({{0, 2}, {0, 0}, {4, 2}, {4, 0}}, 2),
                                new DataBuffer3({norm2, norm2, norm2, norm2}, 3), parent);
    }
    void add_children(Scene *scene) {
        for (int i = 0; i < 8; ++i)
            scene->add(parts[i]);
    }
    ~House() {
        for (int i = 0; i < 8; ++i)
            delete parts[i];
    }
};


class HouseScene : public Scene {
private:
    Drawable *floor;
    House *house;
public:
    HouseScene(Camera *camera) : Scene("House", 1000, 700, camera),
                                 floor(nullptr) { }

    void init() {
        floor = new Floor(center);
        house = new House(center);
        add(floor);
        house->add_children(this);
        set_wheel_callback(scroll);
    }

    virtual ~HouseScene() {
        if (floor != nullptr)
            delete floor;
        if (house != nullptr)
            delete house;
    }

    virtual void process_events() {
        if (key_state(GLFW_KEY_LEFT))
            center->move_horizontal(.2f);
        if (key_state(GLFW_KEY_RIGHT))
            center->move_horizontal(-.2f);
        if (key_state(GLFW_KEY_UP))
            center->move_vertical(-.2f);
        if (key_state(GLFW_KEY_DOWN))
            center->move_vertical(.2f);
    }

    void before_iteration(float time) {
        ::program->set_uniform("lightPosition",
                               glm::vec3(center->get_model(time) * glm::rotateX(glm::vec4(10, 20, 0, 1), time * .5f)));
        ::program->set_uniform("lightColor", {.9, .9, .9});
        ::program->set_uniform("ambientLight", {.2, .2, .2});
    }

};


int main() {
    camera = new PerspectiveCamera(1000, 700, 1.5, 1, 200);
    HouseScene *scene = new HouseScene(camera);
    center = new Center();
    program = new MvpProgram("shaders/mvp_vertex.glsl", "shaders/texture_fragment.glsl");
    camera->look_at(glm::vec3(0, cam_dist * .6f, cam_dist), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    scene->init();

    scene->run();

    delete center;
    delete scene;
    delete camera;
    delete program;
    return 0;
}