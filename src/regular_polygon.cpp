#include "regular_polygon.h"


RegularPolygon::RegularPolygon(GLsizei sides, float radio) :
        Buffer(0), sides(sides) {
    _data = new glm::vec2[sides];
    for (GLsizei i = 0; i < sides; ++i) {
        float angle = float(i * 2 * M_PI / sides);
        _data[i] = {radio * GLfloat(cos(angle)), radio * GLfloat(sin(angle))};
    }
}


RegularPolygon::~RegularPolygon() {
    delete[] _data;
}


const void * RegularPolygon::data() const {
    return _data;
}


GLsizeiptr RegularPolygon::data_size() const {
    return sizeof(glm::vec2) * sides;
}


GLsizei RegularPolygon::size() const {
    return sides;
}


GLint RegularPolygon::dimension() const {
    return 2;
}
