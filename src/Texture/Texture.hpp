#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "../Shader/Shader.hpp"

class Texture {
private:

public:
    GLuint ID;
    GLenum type;

    Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};

#endif
