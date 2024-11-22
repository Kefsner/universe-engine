#pragma once
#include "engine/renderer/renderer_api.hpp"

namespace Universe {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}