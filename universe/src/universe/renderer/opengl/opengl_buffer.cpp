#include "pch.hpp"

#include <glad/glad.h>

#include "universe/renderer/opengl/opengl_buffer.hpp"

namespace Universe
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        glCreateBuffers(1, &m_VertexBufferID);
        glNamedBufferData(m_VertexBufferID, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_VertexBufferID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}