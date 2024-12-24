#pragma once

#include <glm/glm.hpp>

#include "universe/base/base.hpp"
#include "universe/renderer/renderer_api.hpp"

namespace Universe
{
    class RenderCommand
    {
    public:
        static void Init();

        static void SetClearColor(const glm::vec4& color);
        static void Clear();

        static void DrawArrays(uint32_t first, uint32_t count);
        static void DrawIndexed(uint32_t count);

    private:
        static Scope<RendererAPI> s_RendererAPI;
    };
}