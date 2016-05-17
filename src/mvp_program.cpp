#include "mvp_program.h"


MvpProgram::MvpProgram(const char *vertex_shader, const char *fragment_shader) :
    Program(vertex_shader, fragment_shader) { }


void MvpProgram::set_mvp(glm::mat4 mvp) {
    set_uniform("MVP", mvp);
}


void MvpProgram::set_m(glm::mat4 m) {
    set_uniform("M", m);
}


void MvpProgram::set_v(glm::mat4 v) {
    set_uniform("V", v);
}
