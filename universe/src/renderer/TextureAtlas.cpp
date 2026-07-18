#include "renderer/TextureAtlas.hpp"

#include <universe.hpp>

namespace Universe
{
    TextureAtlas::TextureAtlas(std::shared_ptr<Texture> texture, int rows, int columns)
        : m_Texture(texture), m_Rows(rows), m_Columns(columns)
    {
    }

    glm::vec2 TextureAtlas::GetTexCoordFromID(int ID)
    {
        int row = ID / m_Columns;
        int column = ID % m_Columns;

        float cellWidth = m_Columns / m_Texture->GetWidth();
        float cellHeight = m_Rows / m_Texture->GetHeight();

        float u = column * cellWidth;
        float v = row * cellHeight;

        return {u, v};
    }
}