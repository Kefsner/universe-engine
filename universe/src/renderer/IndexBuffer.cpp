#include "renderer/IndexBuffer.hpp"

namespace Universe
{
    IndexBuffer::IndexBuffer()
    {
        glCreateBuffers(1, &m_ID);
    }

    void IndexBuffer::SetData(const unsigned int* indices, int count)
    {
        glNamedBufferData(m_ID, count*sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
    }
}