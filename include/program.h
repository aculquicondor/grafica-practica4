#ifndef HELLO_OPENGL_PROGRAM_H
#define HELLO_OPENGL_PROGRAM_H

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>


class Program {
private:
    GLuint program_id;
    std::map<std::string, GLint> uniforms;

    GLint set_uniform(const std::string &name);
public:
    Program(const char *vertex_shader, const char *fragment_shader);
    virtual void activate() const;

    void set_uniform(const std::string &name, glm::vec3 value);
    void set_uniform(const std::string &name, glm::vec4 value);
    void set_uniform(const std::string &name, glm::mat4 value);
    void set_uniform(const std::string &name, const std::vector<glm::vec4> value);
    void set_uniform(const std::string &name, float value);
};

#endif //HELLO_OPENGL_PROGRAM_H
