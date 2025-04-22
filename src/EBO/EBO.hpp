#ifndef EBO_HPP
#define EBO_HPP

#include <glad/glad.h>

class EBO {
private:


public:
    GLuint ID;
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};

#endif
