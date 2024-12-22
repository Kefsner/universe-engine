#include "pch.hpp"

#include <glad/glad.h>

#include "universe/renderer/opengl/opengl_vertex_array.hpp"

namespace Universe
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_VertexArrayID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_VertexArrayID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_VertexArrayID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        glVertexArrayVertexBuffer(m_VertexArrayID, 0, vertexBuffer->GetVertexBufferID(), 0, sizeof(float) * 2);
        glVertexArrayAttribFormat(
            m_VertexArrayID,
            0, // Matches layout(location = 0) in the vertex shader
            2, // Number of components (e.g., 2 for vec2)
            GL_FLOAT, // Data type (float)
            GL_FALSE, // Not normalized
            0 // Offset within the vertex (starts at the beginning)
        );
        glVertexArrayAttribBinding(m_VertexArrayID, 0, 0);
        glEnableVertexArrayAttrib(m_VertexArrayID, 0);
    }
}