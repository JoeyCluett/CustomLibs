#ifndef __JJC__VERTEX__BUFFER__OBJECT__H__
#define __JJC__VERTEX__BUFFER__OBJECT__H__

/*

*/

// OpenGL includes
#include <GL/glew.h> // this needs to be included before glfw3 headers
#include <GLFW/glfw3.h>

namespace Util {

class VertexBufferObject {
private:
    // OpenGL identifier
    GLuint __vbo = 0;

    // data for the call to glVertexAttribPointer
    int __attrib_index;
    int __element_size;
    int __def_type;
    GLboolean __normalized = GL_FALSE;

public:
    // constructor makes __vbo legit for OpenGL
    VertexBufferObject(void);

    // add data to this VertexBufferObject
    void bufferData(const void* data, int __size);

    // the OpenGL id of this VertexBufferObject
    GLuint getID(void) { return __vbo; }

    // bind to the current OpenGL context
    void bind(void);

    // setup the pointer OpenGL will use for this VBO
    void setAttribPtrData(int index, int element_size, int def_type, GLboolean normalized = GL_FALSE);

    // generate an attribute pointer for OpenGL
    void generateAttribPointer(void);
};

VertexBufferObject::VertexBufferObject(void) {
    glGenBuffers(1, &__vbo);
}

void VertexBufferObject::bufferData(const void* data, int __size) {
    glBufferData(GL_ARRAY_BUFFER, __size, data, GL_STATIC_DRAW);
}

void VertexBufferObject::bind(void) {
    glBindBuffer(GL_ARRAY_BUFFER, __vbo);
}

void VertexBufferObject::setAttribPtrData(int index, int element_size, int def_type, GLboolean normalized) {
    this->__attrib_index = index;
    this->__element_size = element_size;
    this->__def_type     = def_type;
    this->__normalized   = normalized;
}

void VertexBufferObject::generateAttribPointer(void) {
    glVertexAttribPointer(
        __attrib_index,
        __element_size,
        __def_type,
        __normalized,
        0, 0
    );
}

} // namespace Util

#endif // __JJC__VERTEX__BUFFER__OBJECT__H__
