#ifndef __JJC__STL__MODEL__H__
#define __JJC__STL__MODEL__H__

/*
    STL models require flat shading because
    no color information is given

    STL files are not ideal for rendering because
    every triangle is explicitly defined by 3
    seperate vertices, each taking 12 bytes of data

    3 vertices/tri * 12 bytes/vertex = 36 bytes/triangle
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

#include <vector>
#include <fstream>
#include <iostream>

namespace Model {

class StlModel {
private:
    Util::VertexArrayObject  vao;
    Util::VertexBufferObject vbo_pts, vbo_col;
    Util::Shader             shader;

    // Model transform
    glm::mat4 __Translation, __Rotation, __Scale;

    // for the rest of the MVP matrix
    glm::mat4 __View, __Projection;

    GLuint MVP_Matrix_ID;
    GLuint COLOR_ID;

    // need to ensure data is added as x/y/z
    float* pts_arr;
    int num_floats;

    glm::vec3 color;
    glm::vec3 orig_translation;

    bool modelLoaded = false;

    glm::vec3* vec_arr = 0;

public:
    // default constructor
    StlModel(void) { ; }
    StlModel(std::string filename) {
        loadModelFromFile(filename);
    }

    void loadModelFromFile(std::string filename);

    void setShader(Util::Shader shader) {
        this->shader = shader;
        MVP_Matrix_ID = shader.getUniformLocation("MVP");
        COLOR_ID      = shader.getUniformLocation("COLOR");
    }

    // set the View and Projection matrices for this SimpleCube
    void setViewProjection(glm::mat4 View, glm::mat4 Projection) {
        this->__View = View;
        this->__Projection = Projection;
    }

    // apply scale
    void applyScale(GLfloat x, GLfloat y, GLfloat z);

    // apply translation
    void applyTranslation(GLfloat x, GLfloat y, GLfloat z);

    // set scale, rotation, translation of this quad
    void setScale(GLfloat x, GLfloat y, GLfloat z) {
        __Scale = glm::scale(glm::vec3(x, y, z));
    }

    void setRotation(GLfloat rad, GLfloat x, GLfloat y, GLfloat z) {
        __Rotation = glm::rotate(rad, glm::vec3(x, y, z));
    }

    void setTranslation(GLfloat x, GLfloat y, GLfloat z) {
        __Translation = glm::translate(glm::mat4(), glm::vec3(x, y, z));
    }

    // get overall Model transformation
    glm::mat4 getTf(void) {
        return __Translation * __Rotation * __Scale;
    }

    // set single color used for entire model
    void setColor(GLfloat r, GLfloat g, GLfloat b) { color = glm::vec3(r, g, b); }

    // load vao with data from vbo
    void finalize(void);

    // used during render sequence
    void render(void);
};

void StlModel::loadModelFromFile(std::string filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    char header[80];

    // useless header data
    file.read(header, 80);

    uint32_t num_tris;
    file.read((char*)&num_tris, 4);
    num_floats = num_tris*9;

    std::cout << "Header: ";
    std::cout.write(header, 80);
    std::cout << "\nNumber of faces: " << num_tris << std::endl;

    pts_arr = new float[num_tris * 9]; // each tri has 9 associated floats

    char normal_waste_space[12];
    char attribute_waste_space[2];

    for(int i = 0; i < num_tris; i++) {
        file.read(normal_waste_space, 12);   // normal vector
        file.read((char*)(pts_arr+(i*9)), 36); // 3 point vectors
        file.read(attribute_waste_space, 2); // attribute byte count
    }

    modelLoaded = true;
}

void StlModel::finalize(void) {
    if(!modelLoaded) {
        std::cout << "No model loaded" << std::endl;
        exit(1);
    }

    // verified that the model is loaded, give to OpenGL
    vao.bind();
        // only data shader needs is position data and a color for the entire model
        vbo_pts.bind();
        vbo_pts.bufferData(pts_arr, 4*num_floats);
        vbo_pts.setAttribPtrData(0, 3, GL_FLOAT, GL_FALSE);
}

void StlModel::render(void) {
    glm::mat4 mvp = __Projection * __View * this->getTf();

    vao.bind();
    shader.bind();

    glUniformMatrix4fv(MVP_Matrix_ID, 1, GL_FALSE, &mvp[0][0]);
    glUniform3fv(COLOR_ID, 1, (GLfloat*)&color);

    vao.enableAttribute(0);

    vbo_pts.bind();
    vbo_pts.generateAttribPointer();
    glDrawArrays(GL_TRIANGLES, 0, num_floats);

    vao.disableAttribute(0);
}

}

#endif // __JJC__STL__MODEL__H__







