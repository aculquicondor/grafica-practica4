#ifndef HELLO_OPENGL_GLFW_APPLICATION_H
#define HELLO_OPENGL_GLFW_APPLICATION_H

#include <iostream>
#include <vector>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "drawable.h"
#include "camera.h"

class Scene {
private:
    GLFWwindow *window;
    std::vector<Drawable *> drawables;
    Camera* camera;

protected:
    virtual void before_iteration(float time);
    virtual void process_events();

public:
    Scene(const char *title, int width, int height, Camera *camera);
    virtual ~Scene();
    void run();
    void add(Drawable *drawable);
    int key_state(int key) const;
    std::pair<double, double> cursor_pos() const;
    void set_wheel_callback(GLFWscrollfun callback);
};


#endif //HELLO_OPENGL_GLFW_APPLICATION_H
