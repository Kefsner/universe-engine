#include "core/Logger.hpp"

#include "renderer/VertexBuffer.hpp"

#include <glm/glm.hpp>

namespace Universe
{
    VertexBuffer::VertexBuffer()
    {
        glCreateBuffers(1, &m_ID);
    }

    
    void VertexBuffer::SetData(const float* vertices, int count)
    {
        glNamedBufferData(m_ID, count*sizeof(float), vertices, GL_STATIC_DRAW);
    }

    GLsizei VertexBuffer::GetStride() const
    {
        return 3*sizeof(float);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
    }
}