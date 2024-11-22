#include "engine/renderer/renderer.hpp"
#include "engine/logger/logger.hpp"

namespace Universe {

    RendererAPI Renderer::s_API = RendererAPI::OpenGL;

    void Renderer::BeginScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
    {
        shader->Bind();
        vertexArray->Bind();
        // Draw call
        UE_CORE_INFO("Drawing!");

    }

    void Renderer::EndScene()
    {
    }
}
