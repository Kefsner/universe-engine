#pragma once

#include "universe/renderer/animation.hpp"

namespace Universe
{
    class AssetManager
    {
    public:
        static AssetManager& GetInstance()
        {
            static AssetManager instance;
            return instance;
        }

        Ref<Animation> LoadAnimation(
            const std::string& path,
            uint32_t rows, uint32_t columns,
            float frameDuration = 0.1f, bool loop = true
        );
        
        Ref<Texture2D> GetOrLoadTexture(std::unordered_map<std::string, Ref<Texture2D>>& textureMap,
                                 const std::string& path);
    private:
        AssetManager() = default;
        ~AssetManager() = default;

        // Disable copy and move semantics
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;
        AssetManager(AssetManager&&) = delete;
        AssetManager& operator=(AssetManager&&) = delete;

        std::unordered_map<std::string, Ref<Animation>> m_Animations;
        std::unordered_map<std::string, Ref<Texture2D>> m_Textures;

        mutable std::mutex m_Mutex;
    };
} 