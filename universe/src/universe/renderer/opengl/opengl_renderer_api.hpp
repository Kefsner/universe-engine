#pragma once

#include <glm/glm.hpp>

#include "universe/renderer/renderer_api.hpp"

namespace Universe
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Clear() override;
        virtual void SetClearColor(const glm::vec4& color) override;

        virtual void DrawArrays(uint32_t mode, uint32_t first, uint32_t count) override;
    };
}