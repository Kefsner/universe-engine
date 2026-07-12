#pragma once

#include "renderer/IndexBuffer.hpp"
#include "renderer/VertexBuffer.hpp"
#include "renderer/VertexArray.hpp"
#include "renderer/Shader.hpp"

#include <memory>

namespace Universe
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer() = default;

        void SetPolygonModeLine(bool enabled);

        void DrawSprite(); // TODO: Attach Texture;

    private:
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;

        std::unique_ptr<Shader> m_Shader;

        bool m_PolygonModeLine = false;
    };
}