#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb/stb_image.h>

#include <iostream>

#include "Shader/Shader.hpp"
#include "VBO/VBO.hpp"
#include "VAO/VAO.hpp"
#include "EBO/EBO.hpp"
#include "Texture/Texture.hpp"

const int width = 800, height = 800;

GLfloat vertices[] = {
    /* Coordinates (XYZ)    Colors (RGB)        UV */
    -0.5f, -0.5f,  0.0f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f,  0.0f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
     0.5f,  0.5f,  0.0f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
     0.5f, -0.5f,  0.0f,    1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
};

GLuint indices[] = {
    0, 2, 1,
    0, 3, 2,
};

int main() {
    // Init glfw
    glfwInit();

    // Especify glfw version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    // Create window
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Set window as current context
    glfwMakeContextCurrent(window);

    // Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Initialize viewport
    glViewport(0, 0, width, height);

    Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    Texture popCat("assets/images/cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    popCat.texUnit(shaderProgram, "tex0", 0);

    // Loop until the user closes the window
    while(!glfwWindowShouldClose(window)) {
        // Process input
        // Update game state

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw your objects here
        shaderProgram.Activate();

        glUniform1f(uniID, 1.5f);
        popCat.Bind();

        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    popCat.Delete();
    glfwDestroyWindow(window);

    // Clean up resources
    glfwTerminate();
}
