#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
// #include <stb/stb_image.h>

#include <iostream>

#include "Shader/Shader.hpp"
#include "VBO/VBO.hpp"
#include "VAO/VAO.hpp"
#include "EBO/EBO.hpp"

const int width = 800, height = 800;

GLfloat vertices[] = {
    /* Coordinates (XYZ) */                         /* Colors (RGB) */
    -0.5f,  -0.5f * float(sqrt(3)) / 3,   0.0f,     0.8f,  0.3f,  0.02f,
     0.5f,  -0.5f * float(sqrt(3)) / 3,   0.0f,     0.8f,  0.3f,  0.02f,
     0.0f,   0.5f * float(sqrt(3)) * 2/3, 0.0f,     1.0f,  0.6f,  0.32f,
    -0.25f,  0.5f * float(sqrt(3)) / 6,   0.0f,     0.9f,  0.45f, 0.17f,
     0.25f,  0.5f * float(sqrt(3)) / 6,   0.0f,     0.9f,  0.45f, 0.17f,
     0.0f,  -0.5f * float(sqrt(3)) / 3,   0.0f,     0.8f,  0.3f,  0.02f,
};

GLuint indices[] = {
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
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

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

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

        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);

    // Clean up resources
    glfwTerminate();
}
