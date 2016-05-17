#include "uniform_color.h"


UniformColor::UniformColor(const glm::vec4 &color, GLsizei size) :
        Buffer(1), _size(size) {
    _data = new glm::vec4[size];
    for (GLuint i = 0; i < size; ++i)
        _data[i] = color;
}


UniformColor::~UniformColor() {
    delete _data;
}


const void *UniformColor::data() const {
    return _data;
}


GLsizeiptr UniformColor::data_size() const {
    return _size * sizeof(glm::vec4);
}


GLsizei UniformColor::size() const {
    return _size;
}


GLint UniformColor::dimension() const {
    return 4;
}
