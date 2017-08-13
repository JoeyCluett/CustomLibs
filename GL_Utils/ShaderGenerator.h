#ifndef __JJC__SHADER__GENERATOR__H__
#define __JJC__SHADER__GENERATOR__H__

#include <iostream>
#include <string.h>
#include <string>

#include <GL/glew.h> // this needs to be included before glfw3 headers
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// CustomLibs
#include <MISC/FileLoader.h>
#include <MISC/conio.h>

/*
    Compile shader to object code
    Link multiple object
*/

enum ShaderType {
    VERTEX = 0, FRAGMENT = 1
};

class ShaderGenerator {
private:
    static std::string __directory;

public:
    // compiles a given files contents as a shader object file
    static GLuint compile(std::string filename, ShaderType __type, bool __debug = true);

    // links multiple pre-compiled object files into a single shader executable
    static GLuint link(GLuint vertex_shader, GLuint fragment_shader);

    // fully compiles two shader source files into a single shader program
    static GLuint createProgram(std::string vertex_shader_file, std::string fragment_shader_file);

    // specify a directory to search for files
    static void setDirectory(std::string directory);
};

std::string ShaderGenerator::__directory = std::string("");

void ShaderGenerator::setDirectory(std::string directory) {
    __directory = directory;
}

GLuint ShaderGenerator::compile(std::string filename, ShaderType __type, bool __debug) {
    filename = __directory + filename;

    if(__debug) {
        if(__type == ShaderType::VERTEX)
            std::cout << "Src: " << filename << "\nType: VERTEX\n";
        if(__type == ShaderType::FRAGMENT)
            std::cout << "Src: " << filename << "\nType: FRAGMENT\n";
    }

    GLuint shader_id;

    if(__type == ShaderType::VERTEX)
        shader_id = glCreateShader(GL_VERTEX_SHADER);
    else
        shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    std::string contents = LoadFileToString(filename);

    char const* sourcePtr = (char*)contents.c_str();

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

        std::cerr << "shader compile error: " << filename << std::endl;
        std::cerr << "Error log:\n    " << error_log << std::endl;
        std::cerr << "See INFO? y/n ";

        int ch = getch();

        if(ch == 'y') {
            std::cerr << std::endl << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
            std::cerr << "GLSL version:   " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
            std::cerr << "GL vendor:      " << glGetString(GL_VENDOR) << std::endl;
            std::cerr << "GL renderer:    " << glGetString(GL_RENDERER) << std::endl;
            //std::cerr << "GL extensions:  " << glGetString(GL_EXTENSIONS) << std::endl;
        } else {
            std::cerr << std::endl;
        }

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
        std::cout << "shader program link error" << std::endl;
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

#endif // __JJC__SHADER__GENERATOR__H__










