#ifndef __JJC__SHADER__H__
#define __JJC__SHADER__H__

#include <string.h>
#include <string>

// OpenGL includes
#include <GL/glew.h> // this needs to be included before glfw3 headers
#include <GLFW/glfw3.h>

#include <GL_Utils/ShaderGenerator.h>

namespace Util {

class Shader {
private:
    GLuint shader_program;
    GLuint vertex_shader;
    GLuint fragment_shader;

public:
    // constructor demands filenames for both shader files
    Shader(std::string loc_vertex_shader, std::string loc_fragment_shader);

    // constructor allows a prefix for the files
    Shader(std::string _prefix, std::string loc_vertex_shader, std::string loc_fragment_shader);

    // default constructor
    Shader(void) { ; }

    // get compiled fragment shader ID
    GLuint getFragmentShader(void) { return fragment_shader; }

    // get compiled vertex shader ID
    GLuint getVertexShader(void) { return vertex_shader; }

    // get the address of a uniform location in this Shader
    GLuint getUniformLocation(std::string uniform_name);

    // bind before using shader to render
    void bind(void);
};

Shader::Shader(std::string loc_vertex_shader, std::string loc_fragment_shader) {
    ShaderGenerator::setDirectory("");

    vertex_shader   = ShaderGenerator::compile(loc_vertex_shader, ShaderType::VERTEX);
    fragment_shader = ShaderGenerator::compile(loc_fragment_shader, ShaderType::FRAGMENT);

    shader_program = ShaderGenerator::link(vertex_shader, fragment_shader);
}

Shader::Shader(std::string _prefix, std::string loc_vertex_shader, std::string loc_fragment_shader) {
    ShaderGenerator::setDirectory(_prefix);

    vertex_shader   = ShaderGenerator::compile(loc_vertex_shader,   ShaderType::VERTEX);
    fragment_shader = ShaderGenerator::compile(loc_fragment_shader, ShaderType::FRAGMENT);

    shader_program = ShaderGenerator::link(vertex_shader, fragment_shader);
}

void Shader::bind(void) {
    glUseProgram(shader_program);
}

GLuint Shader::getUniformLocation(std::string uniform_name) {
    return glGetUniformLocation(shader_program, (char*)uniform_name.c_str());
}

} // namespace Util

#endif // __JJC__SHADER__H__
