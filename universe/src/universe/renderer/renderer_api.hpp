#pragma once

#include <glm/glm.hpp>

#include "universe/base/base.hpp"

namespace Universe
{
    class RendererAPI
    {
    public:
        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;

        virtual void DrawArrays(uint32_t mode, uint32_t first, uint32_t count) = 0;

        static Scope<RendererAPI> Create();
    };
}