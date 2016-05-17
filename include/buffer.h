#ifndef HELLO_OPENGL_BUFFER_H
#define HELLO_OPENGL_BUFFER_H

#include "GL/glew.h"


class Buffer {
private:
    GLuint location;
    bool data_loaded;

    void load_data() const;

protected:
    GLuint buffer_id;

    virtual const void * data() const = 0;
    virtual GLsizeiptr data_size() const = 0;

public:
    Buffer(GLuint location=0);
    virtual ~Buffer();
    void activate() const;
    void deactivate() const;

    virtual GLint dimension() const;
    virtual GLenum data_type() const;
    virtual GLsizei size() const = 0;
};

#endif //HELLO_OPENGL_GEOMETRY_H
