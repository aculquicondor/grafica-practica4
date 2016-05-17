#ifndef HELLO_OPENGL_UNIFORM_COLOR_H
#define HELLO_OPENGL_UNIFORM_COLOR_H


#include <glm/vec4.hpp>

#include "buffer.h"


class UniformColor : public Buffer {
private:
    glm::vec4 *_data;
    GLsizei _size;

    virtual const void * data() const;
    virtual GLsizeiptr data_size() const;
public:
    UniformColor(const glm::vec4 &color, GLsizei size);
    virtual ~UniformColor();

    virtual GLsizei size() const;
    virtual GLint dimension() const;
};

#endif //HELLO_OPENGL_UNIFORM_COLOR_H
