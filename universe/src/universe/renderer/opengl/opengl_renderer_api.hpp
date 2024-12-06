#pragma once

#include "universe/renderer/renderer_api.hpp"

namespace Universe {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
        virtual void Clear() override;
    };
} 