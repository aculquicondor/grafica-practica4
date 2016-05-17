#ifndef HELLO_OPENGL_GIZMO_H
#define HELLO_OPENGL_GIZMO_H

#include "drawable.h"
#include "mvp_program.h"


class Gizmo : public Buffer, public Drawable {
private:
    static const GLfloat _data[18];

    virtual const void * data() const;
    virtual GLsizeiptr data_size() const;
    virtual GLsizei size() const;
public:
    Gizmo(MvpProgram *program, Drawable *parent = nullptr);
    virtual ~Gizmo();
};


class GizmoColor : public Buffer {
private:
    static const GLfloat _data[18];

    virtual const void * data() const;
    virtual GLsizeiptr data_size() const;
    virtual GLsizei size() const;
public:
    GizmoColor();
    virtual ~GizmoColor();
};

#endif //HELLO_OPENGL_GIZMO_H
