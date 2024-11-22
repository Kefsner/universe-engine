#pragma once
#include "engine/renderer/vertex_array.hpp"

namespace Universe {

    class RendererAPI
    {
    public:
        enum class API {
            None = 0,
            OpenGL
        };

        virtual ~RendererAPI() = default;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        static API GetAPI() { return s_API; }
        static Ref<RendererAPI> Create();

    private:
        static API s_API;
    };
}