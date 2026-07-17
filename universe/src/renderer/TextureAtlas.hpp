#pragma once

#include "renderer/Texture.hpp"

#include <memory>
namespace Universe
{
    class TextureAtlas
    {
    public:
        TextureAtlas(std::shared_ptr<Texture> texture, int width, int height);
        ~TextureAtlas() = default;

        std::pair<float, float> GetUVFromID(int ID);

    private:
        std::shared_ptr<Texture> m_Texture;
        int m_Rows;
        int m_Columns;
    };
}