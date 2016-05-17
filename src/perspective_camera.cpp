#include "perspective_camera.h"


PerspectiveCamera::PerspectiveCamera(int width, int height, float field_of_view,
                                     float near, float far) {
    projection = glm::perspective(field_of_view, (float)width / height, near, far);
    view = glm::mat4(1.0f);
}


glm::mat4 PerspectiveCamera::get_v() const {
    return view;
}

glm::mat4 PerspectiveCamera::get_p() const {
    return projection;
}

void PerspectiveCamera::look_at(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
    view = glm::lookAt(eye, center, up);
}
