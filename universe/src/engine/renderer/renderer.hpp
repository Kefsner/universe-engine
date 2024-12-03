#pragma once

#include "engine/renderer/shader.hpp"
#include "engine/renderer/vertex_array.hpp"
#include "engine/renderer/renderer_command.hpp"
#include "engine/renderer/renderer_api.hpp"
#include "engine/renderer/camera.hpp"

namespace Universe {

    class Renderer
    {
    public:
        static void Init();
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

    class Renderer2D
    {
    public:
        static void Init();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
    };
}