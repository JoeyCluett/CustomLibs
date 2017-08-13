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
bool TextureLoader::__inited = false;
GLuint TextureLoader::__texture_handle = 0;

void TextureLoader::load(std::string filename) {
    if(__inited)
        __texture_handle = ilutGLLoadImage((char*)filename.c_str());
    else {
        std::cerr << "TextureLoader: DevIL not initialized\n";
        std::cerr << "\tCall TextureLoader::InitIL\n";
        exit(-1);
    }
}

void TextureLoader::InitIL(void) {
    ilutRenderer(ILUT_OPENGL);
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
