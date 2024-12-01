#pragma once
#include "engine/renderer/renderer_api.hpp"

namespace Universe {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() override;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
        virtual void Clear() override;
    };
} 