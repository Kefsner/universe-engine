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

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetIndexBufferID() const override { return m_IndexBufferID; }
        virtual uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_IndexBufferID;
        uint32_t m_Count;
    };
}