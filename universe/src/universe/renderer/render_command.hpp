#pragma once

#include "universe/core/core.hpp"
#include "universe/renderer/vertex_array.hpp"
#include "universe/renderer/renderer_api.hpp"

namespace Universe {

    class RenderCommand
    {
    public:
        static void Init()
        {
            s_API->Init();
        }
        
        static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
        {
            s_API->DrawIndexed(vertexArray, indexCount);
        }

        static void SetClearColor(const glm::vec4& color)
        {
            s_API->SetClearColor(color);
        }

        static void Clear()
        {
            s_API->Clear();
        }

        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_API->SetViewport(x, y, width, height);
        }

    private:
        static Ref<RendererAPI> s_API;
    };
}