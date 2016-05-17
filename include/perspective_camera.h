#ifndef HELLO_OPENGL_PERSPECTIVE_CAMERA_H
#define HELLO_OPENGL_PERSPECTIVE_CAMERA_H

#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"


class PerspectiveCamera : public Camera {
private:
    glm::mat4 view;
    glm::mat4 projection;
public:
    PerspectiveCamera(int width, int height, float field_of_view, float near=1, float far=50);
    virtual glm::mat4 get_v() const;
    virtual glm::mat4 get_p() const;
    virtual void look_at(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
};

#endif //HELLO_OPENGL_PERSPECTIVE_CAMERA_H
