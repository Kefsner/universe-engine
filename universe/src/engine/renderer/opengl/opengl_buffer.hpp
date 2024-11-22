#pragma once

#include "engine/renderer/buffer.hpp"

namespace Universe {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        void Bind() const override;

    private:
        uint32_t m_RendererID; // This is used in OpenGL to reference the buffer, glGenBuffers(1, &m_RendererID) generates a buffer and stores the reference in m_RendererID
    };
}