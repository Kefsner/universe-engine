#include "pch.hpp"
#include "engine/renderer/opengl/opengl_vertex_array.hpp"
#include <glad/glad.h>

namespace Universe {

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();
    }

}