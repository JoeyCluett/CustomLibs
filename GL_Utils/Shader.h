#ifndef __JJC__SHADER__H__
#define __JJC__SHADER__H__

#include <iostream>
#include <string.h>
#include <string>

#include <GL/glew.h> // this needs to be included before glfw3 headers
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <MISC/FileLoader.h>

/*
    Compile shader to object code
    Link multiple object
*/

enum ShaderType {
    VERTEX = 0, FRAGMENT = 1
};

class ShaderGenerator {
public:
    // compiles a given files contents as a shader object file
    static GLuint compile(std::string filename, ShaderType __type);

    // links multiple pre-compiled object files into a single shader executable
    static GLuint link(GLuint vertex_shader, GLuint fragment_shader);

    // fully compiles two shader source files into a single shader program
    static GLuint createProgram(std::string vertex_shader_file, std::string fragment_shader_file);
};

GLuint ShaderGenerator::compile(std::string filename, ShaderType __type) {
    GLuint shader_id;

    if(__type == ShaderType::VERTEX)
        shader_id = glCreateShader(GL_VERTEX_SHADER);
    else
        shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    std::string contents = LoadFileToString(filename);

    char* const sourcePtr = (char*)contents.c_str();

    glShaderSource(shader_id, 1, &sourcePtr, NULL);
    glCompileShader(shader_id);

    // check the shader
    GLint result = GL_FALSE;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE) {
        GLint log_length = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

        GLchar* error_log = new GLchar[log_length];
        glGetShaderInfoLog(shader_id, log_length, &log_length, error_log);

        std::cout << error_log << std::endl;

        delete[] error_log;

        glfwTerminate();
        exit(-2);
    }

    return shader_id;
}

GLuint ShaderGenerator::link(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader);
    glAttachShader(program_id, fragment_shader);
    glLinkProgram(program_id);

    // check the program
    GLint result = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);

    if(result == GL_FALSE) {
        GLint log_length = 0;
        glGetShaderiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

        GLchar* error_log = new GLchar[log_length];
        std::cout << error_log << std::endl;
        delete[] error_log;

        glfwTerminate();
        exit(-2);
    }

    return program_id;
}

GLuint ShaderGenerator::createProgram(std::string vertex_shader_file, std::string fragment_shader_file) {
    GLuint vertexShader   = compile(vertex_shader_file,   ShaderType::VERTEX);
    GLuint fragmentShader = compile(fragment_shader_file, ShaderType::FRAGMENT);
    return link(vertexShader, fragmentShader);
}

#endif // __JJC__SHADER__H__










