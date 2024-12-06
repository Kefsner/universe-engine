#pragma once

#include "universe/core/core.hpp"
#include "universe/renderer/camera.hpp"
#include "universe/renderer/shader.hpp"
#include "universe/renderer/vertex_array.hpp"
#include "universe/renderer/renderer_api.hpp"

namespace Universe {

    class Renderer
    {
    public:
        static void Init();
        static void Shutdown();
        static void OnWindowResize(uint32_t width, uint32_t height);
        static void BeginScene(OrthographicCamera& camera);
        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
        static void EndScene();

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static Scope<SceneData> s_SceneData;
    };
}