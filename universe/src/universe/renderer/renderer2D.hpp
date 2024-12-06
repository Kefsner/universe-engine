#pragma once

#include "universe/core/core.hpp"
#include "universe/renderer/camera.hpp"
#include "universe/renderer/shader.hpp"
#include "universe/renderer/vertex_array.hpp"
#include "universe/renderer/texture.hpp"

namespace Universe {

    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
    };
}