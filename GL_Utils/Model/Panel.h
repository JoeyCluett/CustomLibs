#ifndef __JJC__PANEL__H__
#define __JJC__PANEL__H__

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <GL_Utils/VAO.h>
#include <GL_Utils/VBO.h>
#include <GL_Utils/Shader.h>
#include <GL_Utils/Texture.h>

namespace Model {

class Panel {
private:
    // hold references to all the stuff needed for this Panel
    Util::VertexArrayObject _vao;

    // hold position data for each vertex
    Util::VertexBufferObject _vbo_pos;

    // hold coordinate data for texture mapping
    Util::VertexBufferObject _vbo_uv;

    Util::Shader  __shader;
    Util::Texture __texture;

    GLuint __texture_sampler; // ripped from __shader
    GLuint MVP_MatrixID;      // ripped from __shader

    // extra data that can be passed to the shaders
    struct Vec4_Uniform_Wrapper {
        GLuint vec4_id;
        bool use = false;
        glm::vec4 vec;
    };
    struct Mat4_Uniform_Wrapper {
        GLuint mat4_id;
        bool use = false;
        glm::mat4 mat;
    };

    Mat4_Uniform_Wrapper extra_mat4[3];
    Vec4_Uniform_Wrapper extra_vec4[3];

    glm::mat4 __scale, __rotation, __translation;

    glm::mat4 _View, _Projection;

    GLfloat x = 0.0f, y = 0.0f, z = 0.0f;

    GLfloat __pts[18] = {
        -0.5, -0.5, 0.0,
         0.5, -0.5, 0.0,
         0.5,  0.5, 0.0,
        -0.5, -0.5, 0.0,
         0.5,  0.5, 0.0,
        -0.5,  0.5, 0.0
    };

    // UV coordinates
    GLfloat __uv[12] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 0.0,
        1.0, 1.0,
        0.0, 1.0
    };

public:
    Panel(void) { ; }
    Panel(GLfloat height, GLfloat width);

    // set the Shader and Texture of this Panel
    void setShaderTexture(Util::Shader shader, Util::Texture texture);

    GLfloat* getPts(void) { return __pts; }
    GLfloat* getUV(void) { return __uv; }

    void setUVCoordinates(GLfloat* __uv);

    void setViewProjection(glm::mat4 _View, glm::mat4 _Projection) {
        this->_View        = _View;
        this->_Projection  = _Projection;
    }

    glm::mat4 getTf(void) {
        return (__translation * __rotation * __scale);
    }

    void setVec4Uniform(glm::vec4 vec, int vec_index) {
        extra_vec4[vec_index].vec = vec;
        extra_vec4[vec_index].use = true;
    }

    void setMat4Uniform(glm::mat4 mat, int mat_index) {
        extra_mat4[mat_index].mat = mat;
        extra_mat4[mat_index].use = true;
    }

    // generate VBOs with appropiate data
    void finalize(void);

    // render this panel
    void render(void);

    void setScale(GLfloat x, GLfloat y, GLfloat z);
    void setRotation(GLfloat rad, GLfloat x, GLfloat y, GLfloat z);
    void setTranslation(GLfloat x, GLfloat y, GLfloat z);
};

Panel::Panel(GLfloat height, GLfloat width) {
    setScale(height, width, 1);
}

void Panel::setUVCoordinates(GLfloat* uv) {
    __uv[0] = uv[0];
    __uv[1] = uv[1];
    __uv[6] = uv[0];
    __uv[7] = uv[1];
    __uv[4] = uv[4];
    __uv[5] = uv[5];
    __uv[8] = uv[4];
    __uv[9] = uv[5];
    __uv[10] = uv[6];
    __uv[11] = uv[7];
    __uv[2] = uv[2];
    __uv[3] = uv[3];
}

void Panel::finalize(void) {
    _vao.bind();
        // give positional data to OpenGL
        _vbo_pos.bind();
        _vbo_pos.bufferData(__pts, 18*sizeof(GLfloat));
        _vbo_pos.setAttribPtrData(0, 3, GL_FLOAT, GL_FALSE);

        // give uv data to OpenGL
        _vbo_uv.bind();
        _vbo_uv.bufferData(__uv, 12*sizeof(GL_FLOAT));
        _vbo_uv.setAttribPtrData(2, 2, GL_FLOAT, GL_FALSE);
}

void Panel::setTranslation(GLfloat x, GLfloat y, GLfloat z) {
    glm::vec3 _dir(x, y, z);
    __translation = glm::translate(glm::mat4(), _dir);
}

void Panel::setScale(GLfloat x, GLfloat y, GLfloat z) {
    __scale = glm::scale(glm::vec3(x, y, z));
}

void Panel::setRotation(GLfloat rad, GLfloat x, GLfloat y, GLfloat z) {
    glm::vec3 _axis(x, y, z);
    __rotation = glm::rotate(rad, _axis);
}

void Panel::setShaderTexture(Util::Shader shader, Util::Texture texture) {
    this->__shader          = shader;
    this->__texture         = texture;
    this->MVP_MatrixID      = shader.getUniformLocation("MVP");
    this->__texture_sampler = shader.getUniformLocation("TEX");

    extra_mat4[0].mat4_id = shader.getUniformLocation("mat4_extra_0");
    extra_mat4[1].mat4_id = shader.getUniformLocation("mat4_extra_1");
    extra_mat4[2].mat4_id = shader.getUniformLocation("mat4_extra_2");

    extra_vec4[0].vec4_id = shader.getUniformLocation("vec4_extra_0");
    extra_vec4[1].vec4_id = shader.getUniformLocation("vec4_extra_1");
    extra_vec4[2].vec4_id = shader.getUniformLocation("vec4_extra_2");

}

void Panel::render(void) {
    glm::mat4 mvp = _Projection * _View * this->getTf();

    _vao.bind();

    __shader.bind();
    glUniformMatrix4fv(MVP_MatrixID, 1, GL_FALSE, &mvp[0][0]);

    for(int i = 0; i < 3; i++) {
        if(extra_mat4[i].use)
            glUniformMatrix4fv(extra_mat4[i].mat4_id, 1, GL_FALSE, &extra_mat4[i].mat[0][0]);

        if(extra_vec4[i].use)
            glUniform4fv(extra_vec4[i].vec4_id, 1, &extra_vec4[i].vec[0]);
    }

    glActiveTexture(GL_TEXTURE0);
    __texture.bind();
    glUniform1i(__texture_sampler, 0);

    _vao.enableAttribute(0);
    _vbo_pos.bind();
    _vbo_pos.generateAttribPointer();

    _vao.enableAttribute(2);
    _vbo_uv.bind();
    _vbo_uv.generateAttribPointer();

    glDrawArrays(GL_TRIANGLES, 0, 6);

    _vao.disableAttribute(0);
    _vao.disableAttribute(2);
}

} // namespace Model

#endif // __JJC__PANEL__H__










