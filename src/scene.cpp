#include "scene.h"


Scene::Scene(const char *title, int width, int height, Camera *camera) :
        camera(camera) {
    if (!glfwInit()) {
        std::cerr << "ERROR: could not start GLFW3\n";
        exit(1);
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cerr << "ERROR: could not open window with GLFW3\n";
        glfwTerminate();
        exit(2);
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        exit(3);
    }

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cerr << "Renderer: " << renderer << std::endl;
    std::cerr << "OpenGL version supported " << version << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


Scene::~Scene() {
    glfwTerminate();
}


void Scene::before_iteration(float time) {
}


void Scene::run() {
    auto initial_time = std::chrono::high_resolution_clock::now();
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do {
        glfwSwapBuffers(window);

        std::chrono::duration<float> elapsed = std::chrono::high_resolution_clock::now() - initial_time;
        float time = elapsed.count();

        before_iteration(time);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (std::size_t i = 0; i < drawables.size(); ++i)
            drawables[i]->draw(camera, time);

        glfwPollEvents();
        process_events();
    } while (glfwWindowShouldClose(window) == 0);
}


void Scene::add(Drawable *drawable) {
    drawables.push_back(drawable);
}


void Scene::process_events() {
}


int Scene::key_state(int key) const {
    return glfwGetKey(window, key);
}

std::pair<double, double> Scene::cursor_pos() const {
    std::pair<double, double> pos;
    glfwGetCursorPos(window, &pos.first, &pos.second);
    return pos;
};


void Scene::set_wheel_callback(GLFWscrollfun callback) {
    glfwSetScrollCallback(window, callback);
}
