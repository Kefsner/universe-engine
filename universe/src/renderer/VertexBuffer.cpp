#include "renderer/VertexBuffer.hpp"

#include <glm/glm.hpp>

namespace Universe
{
    VertexBuffer::VertexBuffer()
    {
        float vertices[] = {
            // Posx, Posy, Posz,
            // ColorR, ColorG, ColorB
            // texU, texV
            -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,   // Bottom left
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f,   // Bottom right
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,   // Top right
            -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f    // Top left
        };

        glCreateBuffers(1, &m_ID);
        glNamedBufferData(m_ID, 32*sizeof(float), vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
    }
}