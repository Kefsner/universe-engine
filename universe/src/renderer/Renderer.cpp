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

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3({0.0f, 0.0f, -3.0f}));
        m_Shader->SetMat4Uniform(view, "u_View");

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
        m_Shader->SetMat4Uniform(projection, "u_Projection");

        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::DrawCube(std::shared_ptr<Texture> texture, int ID, glm::vec3 position)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        m_Shader->SetMat4Uniform(transform, "u_Transform");

        texture->Bind(m_Shader->GetProgram());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };

    void Renderer::SetPolygonModeLine(bool enabled)
    {
        m_PolygonModeLine = enabled;
        glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
    }
}