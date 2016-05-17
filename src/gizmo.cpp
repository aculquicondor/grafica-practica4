#include "gizmo.h"


Gizmo::Gizmo(MvpProgram *program, Drawable *parent) :
        Buffer(), Drawable(program, this, GL_LINES, new GizmoColor, nullptr, nullptr, nullptr, parent) {
}


Gizmo::~Gizmo() {

}


const GLfloat Gizmo::_data[18] = {
    0.f, 0.f, 0.f,
    1.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 1.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 1.f
};


const void * Gizmo::data() const {
    return (GLvoid *)_data;
}


GLsizeiptr Gizmo::data_size() const {
    return sizeof _data;
}


GLsizei Gizmo::size() const {
    return 6;
}


const GLfloat GizmoColor::_data[18] = {
    .5f, 0.f, 0.f,
    1.f, 0.f, 0.f,
    0.f, .5f, 0.f,
    0.f, 1.f, 0.f,
    0.f, .0f, 5.f,
    0.f, .0f, 1.f,
};


GizmoColor::GizmoColor() : Buffer(1) {
}


GizmoColor::~GizmoColor() {
}


const void * GizmoColor::data() const {
    return (GLvoid *)_data;
}


GLsizeiptr GizmoColor::data_size() const {
    return sizeof _data;
}


GLsizei GizmoColor::size() const {
    return 6;
}
