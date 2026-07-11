#include "Shader.hpp"
#include "Window.hpp"

#include <iostream>
#include <cassert>

#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    spdlog::info("OpenGL DebugCallback:");
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        spdlog::info("  --Severity Notificaion: {}", message);
        break;
    case GL_DEBUG_SEVERITY_LOW:
        spdlog::warn("  --Severity Low: {}", message);
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        spdlog::warn("  --Severity Medium: {}", message);
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        spdlog::error(" --Severity High: {}", message);
        assert(false);
        break;
    default:
        break;
    }
};

int main()
{
    spdlog::info("Welcome to spdlog!");
    
    Universe::WindowProps windowProps{
        .Width = 1920,
        .Height = 1080,
        .Title = "Hello, Universe!",
        .Debug = true
    };

    Universe::Window window = Universe::Window(windowProps);
    
    // Graphics
    /* Vertices Coordinates */
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bottom left
         0.5f, -0.5f, 0.0f, // Bottom right
         0.5f,  0.5f, 0.0f, // Top right
         0.5f, -0.5f, 0.0f // Top left
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint indexBuffer;
    glCreateBuffers(1, &indexBuffer);
    glNamedBufferData(indexBuffer, 6*sizeof(unsigned int), &indices, GL_STATIC_DRAW);

    glDebugMessageCallback(debugCallback, 0);

    GLuint vertexBuffer;
    glCreateBuffers(1, &vertexBuffer);

    GLsizeiptr vertexBufferSize;
    vertexBufferSize = 12*sizeof(float);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glNamedBufferData(vertexBuffer, vertexBufferSize, &vertices, GL_STATIC_DRAW);

    // Vertex Arrao Object
    GLuint vertexArray;
    glCreateVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    
    // glVertexArrayVertexBuffer(vertexArray, 0, vertexBuffer, 0, 0);
    glEnableVertexArrayAttrib(vertexArray, 0);

    GLuint location = 0;
    GLint size = 3;
    GLenum type = GL_FLOAT;

    glVertexAttribPointer(location, size, type, GL_FALSE, 3*sizeof(float), 0);

    Universe::Shader shader = Universe::Shader();

    /* Loop until the user closes the window */
    while (!window.ShouldClose())
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        window.Update();
    }

    glfwTerminate();

    return 0;
}