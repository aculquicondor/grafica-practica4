#include "data_buffer_2.h"


DataBuffer2::DataBuffer2(const std::vector<glm::vec2> &data, GLuint location) : Buffer(location), _data(data) {
}


GLsizei DataBuffer2::size() const {
    return (GLsizei)_data.size();
}


GLsizeiptr DataBuffer2::data_size() const {
    return _data.size() * sizeof(glm::vec2);
}


const void *DataBuffer2::data() const {
    return _data.data();
}


GLint DataBuffer2::dimension() const {
    return 2;
}
