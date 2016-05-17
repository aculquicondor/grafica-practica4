#ifndef HELLO_OPENGL_MVP_PROGRAM_H
#define HELLO_OPENGL_MVP_PROGRAM_H

#include "program.h"


class MvpProgram : public Program {
protected:
    MvpProgram *program;
public:
    MvpProgram(const char *vertex_shader = "shaders/mvp_vertex.glsl",
               const char *fragment_shader = "shaders/color_fragment.glsl");
    void set_mvp(glm::mat4 mvp);
    void set_m(glm::mat4 m);
    void set_v(glm::mat4 v);
};

#endif //HELLO_OPENGL_MVP_PROGRAM_H
