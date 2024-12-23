#pragma once

#include <glm/glm.hpp>

#include "universe/renderer/renderer_api.hpp"

namespace Universe
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        OpenGLRendererAPI();

        virtual void Clear() override;
        virtual void SetClearColor(const glm::vec4& color) override;

        virtual void DrawArrays(uint32_t first, uint32_t count) override;
        virtual void DrawIndexed(uint32_t count) override;
    };
}