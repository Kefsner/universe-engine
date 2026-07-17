#include "core/AssetManager.hpp"

#include <spdlog/spdlog.h>

#include <memory>

namespace Universe
{
    std::vector<std::shared_ptr<Texture>> AssetManager::s_Textures{};

    std::shared_ptr<Texture> AssetManager::LoadTexture(const char* texturePath)
    {
        int count = s_Textures.size();
        std::shared_ptr<Texture> texturePtr = std::make_shared<Texture>(texturePath, count);

        s_Textures.push_back(texturePtr);
        return texturePtr;
    };
}