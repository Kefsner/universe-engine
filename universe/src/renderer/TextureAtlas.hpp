#pragma once

#include "renderer/Texture.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace Universe
{
    class TextureAtlas
    {
    public:
        TextureAtlas(std::shared_ptr<Texture> texture, int rows, int columns);
        ~TextureAtlas() = default;

        std::shared_ptr<Texture> GetTexture() { return m_Texture; }

        glm::vec2 GetTexCoordFromID(int ID);

    private:
        std::shared_ptr<Texture> m_Texture;
        int m_Rows, m_Columns;
    };
}