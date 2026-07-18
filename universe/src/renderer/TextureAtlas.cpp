#include "renderer/TextureAtlas.hpp"

#include <universe.hpp>

namespace Universe
{
    TextureAtlas::TextureAtlas(std::shared_ptr<Texture> texture, int rows, int columns)
        : m_Texture(texture), m_Rows(rows), m_Columns(columns)
    {
    }
}