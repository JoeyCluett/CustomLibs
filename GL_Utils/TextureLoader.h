#ifndef __JJC__TEXTURE__LOADER__H__
#define __JJC__TEXTURE__LOADER__H__

#include <iostream>

#include <GL/glew.h> // this needs to be included before glfw3 headers
#include <GLFW/glfw3.h>

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

class TextureLoader {
private:
    // every texture has a texture handle
    static GLuint __texture_handle;

    static bool __inited;

public:
    // initialize
    static void InitIL(void);

    static void load(std::string filename);

    static GLuint getTextureID(void);
};

// initialize static data members
bool   TextureLoader::__inited = false;
GLuint TextureLoader::__texture_handle = 0;

void TextureLoader::load(std::string filename) {
    /*if(__inited)
        __texture_handle = ilutGLLoadImage((char*)filename.c_str());
    else {
        std::cerr << "TextureLoader: DevIL not initialized\n";
        std::cerr << "\tCall TextureLoader::InitIL\n";
        exit(-1);
    }*/

    ILuint imageID;
    ilGenImages(1, &imageID);
    ilBindImage(imageID);
    ILboolean success = ilLoadImage(filename.c_str());

    if(success) {
        ILinfo imageInfo;
        iluGetImageInfo(&imageInfo);

        if(imageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
            iluFlipImage();

        success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

        if(!success) {
            ILenum error = ilGetError();
            std::cout << "Image conversion failed: error(" << error << ") " << iluErrorString(error) << std::endl;
            exit(-1);
        }

        glGenTextures(1, &__texture_handle);
        glBindTexture(GL_TEXTURE_2D, __texture_handle);

        // set clamping method
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        // set interpolation method
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(
                GL_TEXTURE_2D,                 // type of texture
                0,                             // mipmap level
                ilGetInteger(IL_IMAGE_FORMAT), // internal pixel format
                ilGetInteger(IL_IMAGE_WIDTH),  // image width
                ilGetInteger(IL_IMAGE_HEIGHT), // image height
                0,                             // border width in pixels
                ilGetInteger(IL_IMAGE_FORMAT), // format of image pixel data
                GL_UNSIGNED_BYTE,              // image data type
                ilGetData()                    // image data itself
        );

    } else {
        ILenum error = ilGetError();
        std::cout << "Image load failed: error(" << error << ") " << iluErrorString(error) << std::endl;
        exit(-1);
    }

    ilDeleteImages(1, &imageID);
}

void TextureLoader::InitIL(void) {
//    ilutRenderer(ILUT_OPENGL);
    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
    __inited = true;
}

GLuint TextureLoader::getTextureID(void) {
    return __texture_handle;
}

#endif // __JJC__TEXTURE__LOADER__H__
