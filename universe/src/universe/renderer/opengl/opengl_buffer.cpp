#include "pch.hpp"

#include <glad/glad.h>

#include "universe/renderer/opengl/opengl_buffer.hpp"

namespace Universe
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, uint32_t size)
    {
        glCreateBuffers(1, &m_VertexBufferID);
        glNamedBufferData(m_VertexBufferID, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
    {
        glCreateBuffers(1, &m_VertexBufferID);
        glNamedBufferData(m_VertexBufferID, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_VertexBufferID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    }

    void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
    {
        glNamedBufferData(m_VertexBufferID, size, data, GL_DYNAMIC_DRAW);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
        : m_Count(count)
    {
        glCreateBuffers(1, &m_IndexBufferID);
        glNamedBufferData(m_IndexBufferID, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_IndexBufferID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
    }
}