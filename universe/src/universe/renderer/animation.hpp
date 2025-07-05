#pragma once

#include <glm/glm.hpp>

#include "universe/base/timestep.hpp"
#include "universe/renderer/texture.hpp"

namespace Universe
{
    class Animation
    {
    public:
        Animation(Ref<TextureAtlas> textureAtlas, float frameDuration, bool loop)
            : m_TextureAtlas(textureAtlas), m_FrameDuration(frameDuration), m_Loop(loop)
        {
            m_TotalFrames = textureAtlas->GetRows() * textureAtlas->GetColumns();
        }

        uint32_t GetTotalFrames() const { return m_TotalFrames; }
        float GetFrameDuration() const { return m_FrameDuration; }
        bool IsLooping() const { return m_Loop; }

        Ref<Texture2D> GetTexture() const
        {
            return m_TextureAtlas->GetTexture();
        }

        std::array<glm::vec2, 4> GetFrameUV(uint32_t frameIndex) const
        {
            return m_TextureAtlas->CalculateTextureCoords(frameIndex);
        }

        static Ref<Animation> Create(Ref<TextureAtlas> textureAtlas, float frameDuration, bool loop)
        {
            return CreateRef<Animation>(textureAtlas, frameDuration, loop);
        }

    private:
        Ref<TextureAtlas> m_TextureAtlas;
        float m_FrameDuration;
        bool m_Loop;

        uint32_t m_TotalFrames = 0;
    };
}