#ifndef __JJC__TEXTURE__H__
#define __JJC__TEXTURE__H__

#include <string.h>
#include <string>

// OpenGL includes
#include <GL/glew.h> // this needs to be included before glfw3 headers
#include <GLFW/glfw3.h>

#include <GL_Utils/TextureLoader.h>

namespace Util {

class Texture {
private:
    GLuint texture_id;

public:
    // supply the filename, either absolute or relative
    Texture(std::string filename);

    // supply the filename with a prefix
    Texture(std::string prefix, std::string filename);

    // default constructor
    Texture(void) { ; }

    void bind(void);

    GLuint getID(void) { return texture_id; }
};

Texture::Texture(std::string filename) {
    TextureLoader::load(filename);
    texture_id = TextureLoader::getTextureID();
}

Texture::Texture(std::string prefix, std::string filename) {
    TextureLoader::load(prefix + filename);
    texture_id = TextureLoader::getTextureID();
}

void Texture::bind(void) {
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

} // namespace Util

#endif // __JJC__TEXTURE__H__
