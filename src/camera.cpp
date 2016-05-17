#include "camera.h"


glm::mat4 Camera::get_vp() const {
    return get_p() * get_v();
}
