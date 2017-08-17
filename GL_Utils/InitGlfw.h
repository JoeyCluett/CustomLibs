#ifndef __JJC__INITGLFW__H__
#define __JJC__INITGLFW__H__

#include <iostream>
#include <string.h>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <MISC/RandomNumber.h>

// initialize GLFW with proper versioning, GLEW
GLFWwindow* GLFW_Init(int width, int height, std::string window_title, int v_major, int v_minor,
                      GLboolean forward_compat, GLboolean fullscreen);

// return a random color (R, G, or B)
GLfloat randColor(void);

// ====================================
// function definitions
// ====================================

GLFWwindow* GLFW_Init(int width, int height, std::string window_title, int v_major, int v_minor,
                      GLboolean forward_compat, GLboolean fullscreen) {

    if(!glfwInit()) { // init GLFW3
        std::cerr << "Failed to initialize GLFW3" << std::endl;
        exit(-1);
    } else {
        std::cout << "GLFW3! ";
    }

    glfwWindowHint(GLFW_SAMPLES, 4);                               // 4x anitaliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, v_major);                 // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, v_minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,forward_compat);           // for all dem MacOS users
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // away with old OpenGL

    GLFWwindow* window = 0;

    if(fullscreen)
        window = glfwCreateWindow(width, height, window_title.c_str(), glfwGetPrimaryMonitor(), NULL);
    else
        window = glfwCreateWindow(width, height, window_title.c_str(), NULL, NULL);

    if(!window) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    } else {
        std::cout << "WINDOW! ";
    }

    glfwMakeContextCurrent(window); // init GLEW
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    } else {
        std::cout << "GLEW! ";
    }

    std::cout << "GO!" << std::endl;

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

// return a random number between 0 and 1
GLfloat randColor(void) {
    int r = getRandomNumber();
    r = r % 1001;
    float r_f = (float)r;
    return r_f / 1000;
}

#endif // __JJC__INITGLFW__H__
