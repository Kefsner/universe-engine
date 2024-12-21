#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include "universe/renderer/renderer2D.hpp"


namespace Universe
{
    static unsigned int QuadVAO, QuadVBO, QuadEBO;
    
    void Renderer2D::Init()
    {
        float vertices[] = {
            // Positions       // Colors         // Texture Coords
            -0.5f, -0.5f,      1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom-left
            0.5f, -0.5f,      0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom-right
            0.5f,  0.5f,      0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // Top-right
            -0.5f,  0.5f,      1.0f, 1.0f, 0.0f,  0.0f, 1.0f  // Top-left
        };

        unsigned int indices[] = {
            0, 1, 2, // First triangle
            2, 3, 0  // Second triangle
        };

        // Generate and bind buffers
        glGenVertexArrays(1, &QuadVAO);
        glGenBuffers(1, &QuadVBO);
        glGenBuffers(1, &QuadEBO);

        glBindVertexArray(QuadVAO);

        glBindBuffer(GL_ARRAY_BUFFER, QuadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QuadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Vertex attribute pointers
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0); // Position
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float))); // Color
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float))); // Texture Coords
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    void Renderer2D::Shutdown()
    {
        glDeleteVertexArrays(1, &QuadVAO);
        glDeleteBuffers(1, &QuadVBO);
        glDeleteBuffers(1, &QuadEBO);
    }

    void Renderer2D::BeginScene()
    {
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        // Create transform matrix
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        // Bind and draw the quad
        glBindVertexArray(QuadVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}