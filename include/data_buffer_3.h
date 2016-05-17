#ifndef HELLO_OPENGL_DATA_BUFFER_3_H
#define HELLO_OPENGL_DATA_BUFFER_3_H

#include <vector>

#include <glm/vec3.hpp>

#include "buffer.h"


class DataBuffer3 : public Buffer {
public:
    DataBuffer3(const std::vector<glm::vec3> &data, GLuint location = 0);

    virtual GLsizei size() const;
private:
    std::vector<glm::vec3> _data;

    virtual const void * data() const;
    virtual GLsizeiptr data_size() const;
};

#endif //HELLO_OPENGL_DATA_BUFFER_3_H
