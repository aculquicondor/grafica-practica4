#ifndef HELLO_OPENGL_DATA_BUFFER_2_H
#define HELLO_OPENGL_DATA_BUFFER_2_H

#include <vector>

#include <glm/vec2.hpp>

#include "buffer.h"


class DataBuffer2 : public Buffer {
public:
    DataBuffer2(const std::vector<glm::vec2> &data, GLuint location = 0);

    virtual GLsizei size() const;
private:
    std::vector<glm::vec2> _data;

    virtual const void * data() const;
    virtual GLsizeiptr data_size() const;
    virtual GLint dimension() const;
};

#endif //HELLO_OPENGL_DATA_BUFFER_2_H
