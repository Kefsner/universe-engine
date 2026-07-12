#pragma once

#include "renderer/Renderer.hpp"

#include <spdlog/spdlog.h>

namespace Universe
{
    Renderer::Renderer()
    {
        m_VertexBuffer = std::make_shared<VertexBuffer>();
        m_IndexBuffer = std::make_unique<IndexBuffer>();
        m_VertexArray = std::make_unique<VertexArray>();
        m_VertexArray->AttachBuffers(*m_VertexBuffer, *m_IndexBuffer);
        m_VertexArray->Bind();
        m_Shader = std::make_unique<Shader>();
        m_Shader->Bind();
    }

    void Renderer::DrawQuad()
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };

    void Renderer::SetPolygonModeLine(bool enabled)
    {
        m_PolygonModeLine = enabled;
        glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
    }
}