#ifndef __JJC_FILELOADER__CUSTOM__H__
#define __JJC_FILELOADER__CUSTOM__H__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

std::string LoadFileToString(std::string filename) {
    std::ifstream shader(filename);
    std::stringstream buffer;
    buffer << shader.rdbuf();
    std::string src = buffer.str();
}

#endif // __JJC_FILELOADER__CUSTOM__H__
