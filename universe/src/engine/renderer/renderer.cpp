#include "engine/renderer/renderer.hpp"
#include "engine/logger/logger.hpp"

namespace Universe {

    void Renderer::BeginScene()
    {
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
    {
        shader->Bind();
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }

    void Renderer::EndScene()
    {
    }
}
