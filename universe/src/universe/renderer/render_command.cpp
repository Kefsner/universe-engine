#include "pch.hpp"

#include "universe/renderer/render_command.hpp"

namespace Universe
{
    Scope<RendererAPI> RenderCommand::s_RendererAPI = nullptr;

    void RenderCommand::Init()
    {
        s_RendererAPI = RendererAPI::Create();
    }

    void RenderCommand::Clear()
    {
        s_RendererAPI->Clear();
    }

    void RenderCommand::SetClearColor(const glm::vec4& color)
    {
        s_RendererAPI->SetClearColor(color);
    }

    void RenderCommand::DrawArrays(uint32_t mode, uint32_t first, uint32_t count)
    {
        s_RendererAPI->DrawArrays(mode, first, count);
    }

    void RenderCommand::DrawIndexed(uint32_t count)
    {
        s_RendererAPI->DrawIndexed(count);
    }
}