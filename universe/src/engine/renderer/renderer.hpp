#pragma once

#include <memory>
#include "engine/renderer/shader.hpp"
#include "engine/renderer/vertex_array.hpp"

namespace Universe {

    enum class RendererAPI {
        None = 0,
        OpenGL
    };

    class Renderer {
    public:
        static void BeginScene();
        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
        static void EndScene();

        static RendererAPI GetAPI() { return s_API; }
    private:
        static RendererAPI s_API;
    };
}