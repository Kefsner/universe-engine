#include <mutex>
#include "universe/assets/asset_manager.hpp"

namespace Universe
{
    Ref<Texture2D> AssetManager::GetOrLoadTexture(std::unordered_map<std::string, Ref<Texture2D>>& textureMap,
                                    const std::string& path)
    {
        if (auto it = textureMap.find(path); it != textureMap.end())
            return it->second;

        auto texture = Texture2D::Create(path);
        textureMap.emplace(path, texture);
        return texture;
    }

    Ref<Animation> AssetManager::LoadAnimation(const std::string& path,
                                            uint32_t rows, uint32_t columns,
                                            float frameTime, bool loop)
    {
        std::scoped_lock lock(m_Mutex);

        if (auto it = m_Animations.find(path); it != m_Animations.end())
            return it->second;

        auto texture = GetOrLoadTexture(m_Textures, path);
        auto atlas   = TextureAtlas::Create(texture, rows, columns);
        auto anim    = Animation::Create(atlas, frameTime, loop);

        m_Animations.emplace(path, anim);
        return anim;
    }
}