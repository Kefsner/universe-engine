#include "pch.hpp"

#include "engine/renderer/opengl/opengl_buffer.hpp"
#include <glad/glad.h>

namespace Universe {

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        glCreateBuffers(1, &m_RendererID);
        glNamedBufferData(m_RendererID, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

}