#include "engine/core.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/logger/logger.hpp"

// Temporary
#include "engine/renderer/opengl/opengl_shader.hpp"

namespace Universe {

    Scope<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

    void Renderer::Init()
    {
        RendererCommand::Init();
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
        RendererCommand::Clear();
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RendererCommand::SetViewport(0, 0, width, height);
    }
}
