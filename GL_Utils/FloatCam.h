#ifndef __JJC__FLOAT__CAM__H__
#define __JJC__FLOAT__CAM__H__

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <GL_Utils/Camera.h>   // Camera objects
#include <math.h>

namespace Util {

class FloatCam {
private:
    // FloatCam position
    glm::vec3 position, direction;
    float _horizontal_angle = 0, _vertical_angle = 0;
    GLfloat fov = 45.0;
    GLfloat speed = 3.0;
    GLfloat mouse_speed = 0.05;
    int screenW, screenH;
    GLFWwindow* window;

    bool lock_mouse = true;

public:
    // constructor provides starting position and speed
    FloatCam(glm::vec3 pos, GLfloat speed, int screenW, int screenH, GLfloat mouse_speed, GLFWwindow* window);

    // update the FloatCam
    void update(float deltaTime);

    // set position of camera
    void setPosition(glm::vec3 pos) { this->position = pos; }

    // set the direction the camera is looking at
    void setOrientation(GLfloat horizontal_angle, GLfloat vertical_angle) {
            this->_horizontal_angle = horizontal_angle;
            this->_vertical_angle   = vertical_angle;
    }

    // get the cameras current position
    glm::vec3 getPosition(void) { return position; }

    // get the cameras current direction
    glm::vec3 getDirection(void) { return direction; }

    // return the View matrix from this FloatCam
    glm::mat4 getTf(void);
};

FloatCam::FloatCam(glm::vec3 pos, GLfloat speed, int screenW, int screenH, GLfloat mouse_speed, GLFWwindow* window) {
    this->position    = pos;
    this->speed       = speed;
    this->screenW     = screenW;
    this->screenH     = screenH;
    this->mouse_speed = mouse_speed;
    this->window      = window;
}

void FloatCam::update(float deltaTime) {
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    //if(lock_mouse)
        glfwSetCursorPos(window, screenW/2, screenH/2);

    _horizontal_angle += mouse_speed * deltaTime * float(screenW/2 - xPos);
    _vertical_angle   += mouse_speed * deltaTime * float(screenH/2 - yPos);

    direction = glm::vec3(
            cos(_vertical_angle) * sin(_horizontal_angle),
            sin(_vertical_angle),
            cos(_vertical_angle) * cos(_horizontal_angle)
    );

    glm::vec3 right(
            sin(_horizontal_angle - M_PI/2.0f),
            0,
            cos(_horizontal_angle - M_PI/2.0f)
    );

    // forward
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }

    // backward
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }

    // strafe right
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }

    // strafe left
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    // toggle lock mouse functionality
    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        lock_mouse = !lock_mouse;

}

glm::mat4 FloatCam::getTf(void) {
    return glm::lookAt(
            position,
            position + direction,
            glm::vec3(0, 1, 0)
    );
}

}
#endif // __JJC__FLOAT__CAM__H__
