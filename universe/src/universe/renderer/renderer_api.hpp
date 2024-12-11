#pragma once

#include  <glm/glm.hpp>

#include "universe/renderer/vertex_array.hpp"

namespace Universe {

    class RendererAPI
    {
    public:
        // API types for the renderer
        enum class API {
            None = 0,
            OpenGL
        };

        virtual ~RendererAPI() = default;
        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        static API GetAPI() { return s_API; }
        static Ref<RendererAPI> Create();

    private:
        static API s_API; // The API that the renderer is using
    };
}