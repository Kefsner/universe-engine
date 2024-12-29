#pragma once

#include <glm/glm.hpp>

#include "universe/renderer/camera.hpp"
#include "universe/renderer/texture.hpp"

namespace Universe
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void SetClearColor(const glm::vec4& color);

        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);
    };
}