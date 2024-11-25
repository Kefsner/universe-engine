#include "engine/core.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/logger/logger.hpp"

// Temporary
#include "engine/renderer/opengl/opengl_shader.hpp"

namespace Universe {

    Scope<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }

    void Renderer::EndScene()
    {
    }
}
