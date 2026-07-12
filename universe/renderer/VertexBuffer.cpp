#include "renderer/VertexBuffer.hpp"

namespace Universe
{
    VertexBuffer::VertexBuffer()
    {
        float vertices[] = {
            // Posx, Posy, ColorR, ColorG, ColorB,
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,     // Bottom left
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,     // Bottom right
             0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,     // Top right
            -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f      // Top left
        };

        glCreateBuffers(1, &m_ID);
        glNamedBufferData(m_ID, 24*sizeof(float), vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
    }
}