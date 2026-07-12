#include "IndexBuffer.hpp"

namespace Universe
{
    IndexBuffer::IndexBuffer()
    {
        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
        };
        glCreateBuffers(1, &m_ID);
        glNamedBufferData(m_ID, 6*sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
    }
}