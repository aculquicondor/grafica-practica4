#include "buffer.h"


Buffer::Buffer(GLuint location) : location(location), data_loaded(false) {
    glGenBuffers(1, &buffer_id);
}


Buffer::~Buffer() {
}


void Buffer::load_data() const {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, data_size(), data(), GL_STATIC_DRAW);
}


void Buffer::activate() const {
    if (!data_loaded)
        load_data();
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glVertexAttribPointer(location, dimension(), data_type(), GL_FALSE, 0, nullptr);
}


void Buffer::deactivate() const {
    glDisableVertexAttribArray(location);
}

GLint Buffer::dimension() const {
    return 3;
}

GLenum Buffer::data_type() const {
    return GL_FLOAT;
}
