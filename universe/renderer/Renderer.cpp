#pragma once

#include "renderer/Renderer.hpp"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::DrawSprite(std::shared_ptr<Texture> texture, glm::vec3 position, glm::vec3 scale, float rotate)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::scale(transform, scale);
        transform = glm::rotate(transform, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
        m_Shader->SetMat4Uniform(transform);
        texture->Bind(m_Shader->GetProgram());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };

    void Renderer::SetPolygonModeLine(bool enabled)
    {
        m_PolygonModeLine = enabled;
        glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
    }
}