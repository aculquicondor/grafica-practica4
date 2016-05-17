#include "program.h"


Program::Program(const char *vertex_shader, const char *fragment_shader) {
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_shader, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    } else {
        std::cerr << "Impossible to open " << vertex_shader <<
        ". Are you in the right directory? Don't forget to read the FAQ!\n";
        getchar();
        program_id = 0;
        return;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_shader, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    GLint InfoLogLength;

    // Compile Vertex Shader
    std::cerr << "Compiling shader: " << vertex_shader << std::endl;
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(std::size_t(InfoLogLength + 1));
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        std::cerr << &VertexShaderErrorMessage[0] << std::endl;
    }

    // Compile Fragment Shader
    std::cerr << "Compiling shader: " << fragment_shader << std::endl;
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        std::cerr << &FragmentShaderErrorMessage[0] << std::endl;
    }

    // Link the program
    std::cerr << "Linking program\n";
    program_id = glCreateProgram();
    glAttachShader(program_id, VertexShaderID);
    glAttachShader(program_id, FragmentShaderID);
    glLinkProgram(program_id);

    // Check the program
    glGetProgramiv(program_id, GL_LINK_STATUS, &Result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(std::size_t(InfoLogLength+1));
        glGetProgramInfoLog(program_id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        std::cerr << &ProgramErrorMessage[0] << std::endl;
    }


    glDetachShader(program_id, VertexShaderID);
    glDetachShader(program_id, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
}


void Program::activate() const {
    glUseProgram(program_id);
}


GLint Program::set_uniform(const std::string &name) {
    if (uniforms.find(name) == uniforms.end())
        return uniforms[name] = glGetUniformLocation(program_id, name.c_str());
    else
        return uniforms[name];
}


void Program::set_uniform(const std::string &name, glm::vec3 value) {
    glUniform3f(set_uniform(name), value.x, value.y, value.z);
}


void Program::set_uniform(const std::string &name, glm::vec4 value) {
    glUniform4f(set_uniform(name), value.x, value.y, value.z, value.w);
}


void Program::set_uniform(const std::string &name, glm::mat4 value) {
    glUniformMatrix4fv(set_uniform(name), 1, GL_FALSE, &value[0][0]);
}


void Program::set_uniform(const std::string &name, const std::vector<glm::vec4> value) {
    glUniform4fv(set_uniform(name), (GLsizei)value.size(), &value[0].x);
}


void Program::set_uniform(const std::string &name, float value) {
    glUniform1f(set_uniform(name), value);
}
