#pragma once

#include "universe/renderer/buffer.hpp"

namespace Universe {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        // Constructor and Destructor
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        // Virtual functions
        void Bind() const override;
        void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
        const BufferLayout& GetLayout() const override { return m_Layout; }

    private:
        uint32_t m_VertexBufferID;  // The ID of the vertex buffer
        BufferLayout m_Layout;      // The layout of the vertex buffer
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        // Constructor and Destructor
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer();

        // Virtual functions
        void Bind() const override;
        uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_IndexBufferID;  // The ID of the index buffer
        uint32_t m_Count;         // The number of indices in the index buffer
    };
}