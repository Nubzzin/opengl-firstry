#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
private:


public:
    GLuint ID;
    Shader(const char* vertexPath, const char* fragmentPath);

    void Activate();
    void Delete();
};



#endif
