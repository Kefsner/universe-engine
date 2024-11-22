#pragma once

#include <memory>
#include "engine/renderer/shader.hpp"
#include "engine/renderer/vertex_array.hpp"
#include "engine/renderer/renderer_command.hpp"
#include "engine/renderer/renderer_api.hpp"

namespace Universe {

    class Renderer
    {
    public:
        static void BeginScene();
        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);
        static void EndScene();

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}