#ifndef HELLO_OPENGL_RECTANGLE_H
#define HELLO_OPENGL_RECTANGLE_H

#include "data_buffer_3.h"


class Rectangle : public DataBuffer3 {
public:
    Rectangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
};


#endif //HELLO_OPENGL_RECTANGLE_H
