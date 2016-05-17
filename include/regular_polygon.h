#ifndef HELLO_OPENGL_REGULAR_POLYGON_H
#define HELLO_OPENGL_REGULAR_POLYGON_H

#include <cmath>

#include <glm/vec2.hpp>

#include "buffer.h"


class RegularPolygon : public Buffer {
private:
    GLsizei sides;
    glm::vec2 *_data;

public:
    RegularPolygon(GLsizei sides, float radio=1);
    virtual ~RegularPolygon();

    virtual const void * data() const;
    virtual GLsizeiptr data_size() const;
    virtual GLsizei size() const;
    virtual GLint dimension() const;
};

#endif //HELLO_OPENGL_REGULAR_POLYGON_H
