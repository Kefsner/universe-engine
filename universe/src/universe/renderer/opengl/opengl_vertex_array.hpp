#pragma once

#include <glad/glad.h>

#include "universe/renderer/vertex_array.hpp"

namespace Universe
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) const;
        
    private:
        uint32_t m_VertexArrayID;
    };
}