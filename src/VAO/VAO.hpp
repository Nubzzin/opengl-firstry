#ifndef VAO_HPP
#define VAO_HPP

#include <glad/glad.h>
#include "../VBO/VBO.hpp"

class VAO {
private:


public:
    GLuint ID;
    VAO();

    void LinkVBO(VBO VBO, GLuint layout);
    void Bind();
    void Unbind();
    void Delete();
};

#endif
