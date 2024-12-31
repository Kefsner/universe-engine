#include "pch.hpp"

#include "universe/renderer/texture.hpp"
#include "universe/renderer/opengl/opengl_texture.hpp"

namespace Universe
{
    Ref<Texture2D> Texture2D::Create(std::string path)
    {
        return CreateRef<OpenGLTexture2D>(path);
    }

    Ref<Texture2D> Texture2D::Create(TextureSpecification spec)
    {
        return CreateRef<OpenGLTexture2D>(spec);
    }

    // Atlas
    TextureAtlas::TextureAtlas(Ref<Texture2D>& texture, uint32_t rows, uint32_t columns)
        : m_Texture(texture), m_Rows(rows), m_Columns(columns)
    {
    }

    std::array<glm::vec2, 4> TextureAtlas::CalculateTextureCoords(uint32_t index)
    {
        uint32_t xIndex = index % m_Columns;
        uint32_t yIndex = index / m_Columns;

        float frameWidth = 1.0f / m_Columns;
        float frameHeight = 1.0f / m_Rows;

        float u_min = xIndex * frameWidth;
        float v_min = yIndex * frameHeight;
        float u_max = u_min + frameWidth;
        float v_max = v_min + frameHeight;

        return {
            glm::vec2{ u_min, v_min }, // Bottom-left
            glm::vec2{ u_max, v_min }, // Bottom-right
            glm::vec2{ u_max, v_max }, // Top-right
            glm::vec2{ u_min, v_max }  // Top-left
        };
    }

    Ref<TextureAtlas> TextureAtlas::Create(Ref<Texture2D>& texture, uint32_t rows, uint32_t columns)
    {
        return CreateRef<TextureAtlas>(texture, rows, columns);
    }
}