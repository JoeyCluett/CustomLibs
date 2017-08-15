#ifndef __JJC__VERTEX__ARRAY__OBJECT__H__
#define __JJC__VERTEX__ARRAY__OBJECT__H__

// OpenGL includes
#include <GL/glew.h> // this needs to be included before glfw3 headers
#include <GLFW/glfw3.h>

namespace Util {

class VertexArrayObject {
private:
    // OpenGL identifier
    GLuint __vao = 0;

public:
    // construcor fills __vao with a valid ident for OpenGL
    VertexArrayObject(void);

    // binds this VAO to OpenGL drawing context
    void bind(void);

    // enable the corresponding attribute array pointer
    void enableAttribute(int __index);

    // disable the correspondong attribute pointer
    void disableAttribute(int __index);
};

VertexArrayObject::VertexArrayObject(void) {
    glGenVertexArrays(1, &__vao);
}

void VertexArrayObject::bind(void) {
    glBindVertexArray(__vao);
}

void VertexArrayObject::enableAttribute(int __index) {
    glEnableVertexAttribArray(__index);
}

void VertexArrayObject::disableAttribute(int __index) {
    glDisableVertexAttribArray(__index);
}

} // namespace Util

#endif // __JJC__VERTEX__ARRAY__OBJECT__H__
