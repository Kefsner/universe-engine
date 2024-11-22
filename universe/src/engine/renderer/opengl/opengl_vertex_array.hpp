#pragma once

#include "engine/renderer/vertex_array.hpp"

namespace Universe {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void Bind() const override;

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;

    private:
        uint32_t m_RendererID;
    };
}