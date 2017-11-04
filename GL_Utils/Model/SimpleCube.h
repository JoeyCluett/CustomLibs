#ifndef __JJC__SIMPLE__CUBE__H__
#define __JJC__SIMPLE__CUBE__H__

/*
    SimpleCube is treated much like a Minecraft block
    - all sides are the same texture
    - top and bottom textures can be different from each other
        and from the side texture

    The same vertex and fragment shader is used for the whole SimpleCube
*/

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

class SimpleCube {
private:

    Util::VertexArrayObject  _vao;
    Util::VertexBufferObject _vbo_top, _vbo_side[4], _vbo_bottom, _vbo_uv;

    // for generating the Model transformation matrix
    glm::mat4 __scale, __rotation, __translation;

    // for the rest of the MVP matrix
    glm::mat4 __View, __Projection;

    Util::Shader __shader;
    Util::Texture tex_top, tex_sides, tex_bottom;

    // location in shader of mvp matrix
    GLuint MVP_Matrix_Location, TEX_Sampler_Location;

    // all future translations are added to this before being applied to vertices
    glm::vec3 orig_translation;

    // UV coordinates
    GLfloat __uv[12] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 0.0,
        1.0, 1.0,
        0.0, 1.0
    };

    glm::vec3 __pts[6] = {
        glm::vec3(-0.5, -0.5, 0.5),
        glm::vec3(0.5, -0.5, 0.5),
        glm::vec3(0.5,  0.5, 0.5),
        glm::vec3(-0.5, -0.5, 0.5),
        glm::vec3(0.5,  0.5, 0.5),
        glm::vec3(-0.5,  0.5, 0.5),
    };

    glm::vec3 __pts_top[6], __pts_side[24], __pts_bottom[6];

public:
    SimpleCube(void);
    SimpleCube(GLfloat x_scale, GLfloat y_scale, GLfloat z_scale);

    // set the Shader of this SimpleCube
    void setShader(Util::Shader shader) {
        __shader = shader;
        MVP_Matrix_Location  = shader.getUniformLocation("MVP");
        TEX_Sampler_Location = shader.getUniformLocation("TEX");
    }

    // apply a translation before the cube is finalized
    void applyTranslation(GLfloat x, GLfloat y, GLfloat z);

    // set the texture used on all 4 sides of this SimpleCube
    void setTextureSides( Util::Texture texture) { tex_sides  = texture; }
    void setTextureTop(   Util::Texture texture) { tex_top    = texture; }
    void setTextureBottom(Util::Texture texture) { tex_bottom = texture; }

    // set scale, rotation, translation of this quad
    void setScale(GLfloat x, GLfloat y, GLfloat z) {
        __scale = glm::scale(glm::vec3(x, y, z));
    }
    void setRotation(GLfloat rad, GLfloat x, GLfloat y, GLfloat z) {
        __rotation = glm::rotate(rad, glm::vec3(x, y, z));
    }
    void setTranslation(GLfloat x, GLfloat y, GLfloat z) {
        GLfloat _x = x + orig_translation.x;
        GLfloat _y = y + orig_translation.y;
        GLfloat _z = z + orig_translation.z;
        __translation = glm::translate(glm::mat4(), glm::vec3(_x, _y, _z));
    }

    // set the View and Projection matrices for this SimpleCube
    void setViewProjection(glm::mat4 View, glm::mat4 Projection) {
        this->__View = View;
        this->__Projection = Projection;
    }

    // get overall transformation
    glm::mat4 getTf(void) {
        return __translation * __rotation * __scale;
    }

    // put the SimpleCube into memory
    void finalize(void);

    // render the SimpleCube into the current context
    void render(void);

};

SimpleCube::SimpleCube(void) : SimpleCube(1.0, 1.0, 1.0) {
    ;
}

SimpleCube::SimpleCube(GLfloat x_scale, GLfloat y_scale, GLfloat z_scale) {
    glm::mat4 scale_matrix = glm::scale(glm::vec3(x_scale, y_scale, z_scale));

    glm::vec3 _axis(1, 0, 0);
    glm::mat4 rot_matrix_top = glm::rotate(float(M_PI/-2.0), _axis);
    glm::mat4 rot_matrix_bot = glm::rotate(float(M_PI/2.0), _axis);

    for(int i = 0; i < 6; i++) {
        glm::vec4 tmp_1 = glm::vec4(__pts[i], 1);

        // top face
        glm::vec4 pt_top = rot_matrix_top * tmp_1;
        pt_top = scale_matrix * pt_top;
        __pts_top[i] = glm::vec3(pt_top.x, pt_top.y, pt_top.z);

        // bottom face
        glm::vec4 pt_bot = rot_matrix_bot * tmp_1;
        pt_bot = scale_matrix * pt_bot;
        __pts_bottom[i] = glm::vec3(pt_bot.x, pt_bot.y, pt_bot.z);
    }

    for(int i = 0; i < 4; i++) {
        glm::mat4 rot_matrix_side = glm::rotate(i*float(M_PI/2.0), glm::vec3(0, 1, 0));
        for(int j = 0; j < 6; j++) {
            #define TO_VEC4(v) glm::vec4(v.x, v.y, v.z, 1)
            #define TO_VEC3(v) glm::vec3(v.x, v.y, v.z)
            glm::vec4 tmp = TO_VEC4(__pts_side[6*i + j]);

            tmp = rot_matrix_side * TO_VEC4(__pts[j]);
            tmp = scale_matrix * tmp;

            __pts_side[6*i + j] = TO_VEC3(tmp);
        }
    }
}

void SimpleCube::applyTranslation(GLfloat x, GLfloat y, GLfloat z) {
    orig_translation = glm::vec3(x, y, z);
    setTranslation(0, 0, 0);
}

void SimpleCube::finalize(void) {
    _vao.bind();
        // bind data for top face
        _vbo_top.bind();
        _vbo_top.bufferData(__pts_top, 6*sizeof(glm::vec3));
        _vbo_top.setAttribPtrData(0, 3, GL_FLOAT);

        // bind data for bottom face
        _vbo_bottom.bind();
        _vbo_bottom.bufferData(__pts_bottom, 6*sizeof(glm::vec3));
        _vbo_bottom.setAttribPtrData(0, 3, GL_FLOAT);

        // bind data for side faces
        for(int i = 0; i < 4; i++) {
            _vbo_side[i].bind();
            _vbo_side[i].bufferData(__pts_side+(i*6), 6*sizeof(glm::vec3));
            _vbo_side[i].setAttribPtrData(0, 3, GL_FLOAT);
        }

        // bind uv data for all faces
        _vbo_uv.bind();
        _vbo_uv.bufferData(__uv, 12*sizeof(GLfloat));
        _vbo_uv.setAttribPtrData(2, 2, GL_FLOAT);
}

void SimpleCube::render(void) {
    glm::mat4 mvp = __Projection * __View * this->getTf();

    _vao.bind();
    __shader.bind();
    glUniformMatrix4fv(MVP_Matrix_Location, 1, GL_FALSE, &mvp[0][0]);

    // this is the same for all faces, all UV coordinates
    _vao.enableAttribute(2); // a standard i have adopted
    _vbo_uv.bind();
    _vbo_uv.generateAttribPointer();

    // bind textures to texture units
    glActiveTexture(GL_TEXTURE0); tex_top.bind();
    glActiveTexture(GL_TEXTURE1); tex_bottom.bind();
    glActiveTexture(GL_TEXTURE2); tex_sides.bind();

    // the rest of this changes from texture to texture
    // ==============================================================

    // prep first draw call
    _vao.enableAttribute(0); // only needs to happen once per SimpleCube render cycle
    _vbo_top.bind();
    _vbo_top.generateAttribPointer();
    glUniform1i(TEX_Sampler_Location, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    // prep second draw call
    _vbo_bottom.bind();
    _vbo_bottom.generateAttribPointer();
    glUniform1i(TEX_Sampler_Location, 1);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    // prep third draw call
    glUniform1i(TEX_Sampler_Location, 2);
    for(int i = 0; i < 4; i++) {
        _vbo_side[i].bind();
        _vbo_side[i].generateAttribPointer();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    // ==============================================================

    _vao.disableAttribute(0);
    _vao.disableAttribute(2);
}

} // namespace Model

#endif // __JJC__SIMPLE__CUBE__H__
