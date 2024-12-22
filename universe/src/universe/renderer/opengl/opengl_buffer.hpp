#pragma once

#include "universe/renderer/buffer.hpp"

namespace Universe
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetVertexBufferID() const override { return m_VertexBufferID; }

    private:
        uint32_t m_VertexBufferID;
    };
}