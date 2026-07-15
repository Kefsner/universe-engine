#pragma once

#include "renderer/IndexBuffer.hpp"
#include "renderer/VertexBuffer.hpp"
#include "renderer/VertexArray.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"

#include <memory>

namespace Universe
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer() = default;

        void SetPolygonModeLine(bool enabled);

        void DrawSprite(
            std::shared_ptr<Texture> texture,
            glm::vec3 position,
            glm::vec3 scale = {1.0f, 1.0f, 1.0f},
            float rotate = 0.0f
        );

    private:
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;

        std::unique_ptr<Shader> m_Shader;

        bool m_PolygonModeLine = false;
    };
}