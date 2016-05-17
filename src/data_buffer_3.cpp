#include "data_buffer_3.h"


DataBuffer3::DataBuffer3(const std::vector<glm::vec3> &data, GLuint location) : Buffer(location), _data(data) {
}


GLsizei DataBuffer3::size() const {
    return (GLsizei)_data.size();
}


GLsizeiptr DataBuffer3::data_size() const {
    return _data.size() * sizeof(glm::vec3);
}


const void *DataBuffer3::data() const {
    return _data.data();
}
