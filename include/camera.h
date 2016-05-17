#ifndef HELLO_OPENGL_CAMERA_H
#define HELLO_OPENGL_CAMERA_H

#include <glm/mat4x4.hpp>


class Camera {
public:
    glm::mat4 get_vp() const;
    virtual glm::mat4 get_v() const = 0;
    virtual glm::mat4 get_p() const = 0;
};

#endif //HELLO_OPENGL_CAMERA_H
