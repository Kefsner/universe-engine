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
        uint32_t vertexBufferID = vertexBuffer->GetVertexBufferID();
        const BufferLayout& layout = vertexBuffer->GetLayout();
        glVertexArrayVertexBuffer(m_VertexArrayID, 0, vertexBufferID, 0, layout.GetStride());

        uint32_t index = 0;
        for (const auto& element : layout)
        {
            glVertexArrayAttribFormat(
                m_VertexArrayID,
                index,
                element.numberOfComponents,
                ShaderDataTypeToOpenGLBaseType(element.type),
                element.normalized,
                element.offset
            );
            glVertexArrayAttribBinding(m_VertexArrayID, index, 0);
            glEnableVertexArrayAttrib(m_VertexArrayID, index);
            index++;
        }
    }

    uint32_t OpenGLVertexArray::ShaderDataTypeToOpenGLBaseType(ShaderDataType type) const
    {
        switch (type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_UNSIGNED_BYTE; // OpenGL treats boolean as unsigned byte
            default:
                UE_CORE_ASSERT(false, "Unknown ShaderDataType!");
                return 0;
        }
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glVertexArrayElementBuffer(m_VertexArrayID, indexBuffer->GetIndexBufferID());
    }
}