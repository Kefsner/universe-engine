#pragma once

#include "renderer/Texture.hpp"

#include <vector>
#include <memory>

namespace Universe
{
    class AssetManager
    {
    public:
        static std::shared_ptr<Texture> LoadTexture(const char* texturePath);

    private:
        static std::vector<std::shared_ptr<Texture>> s_Textures;
    };
}
