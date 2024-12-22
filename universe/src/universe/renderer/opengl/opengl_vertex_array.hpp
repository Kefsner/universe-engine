#pragma once

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

    private:
        uint32_t m_VertexArrayID;
    };
}