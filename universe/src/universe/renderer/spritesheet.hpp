#pragma once

#include <glm/glm.hpp>

#include "universe/renderer/texture.hpp"

namespace Universe
{
    class SpriteSheet
    {
    public:
        SpriteSheet(Ref<Texture2D>& texture, uint32_t rows, uint32_t columns);

        std::array<glm::vec2, 4> GetTextureCoords(uint32_t index);

        Ref<Texture2D> GetTexture() const { return m_Texture; }
        
        static Ref<SpriteSheet> Create(Ref<Texture2D>& texture, uint32_t rows, uint32_t columns);

    private:
        Ref<Texture2D> m_Texture;
        uint32_t m_Rows, m_Columns;
    };
}