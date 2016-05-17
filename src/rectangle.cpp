#include "rectangle.h"


Rectangle::Rectangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) : DataBuffer3({p2, p1, p2 + p3 - p1, p3}) {
}
