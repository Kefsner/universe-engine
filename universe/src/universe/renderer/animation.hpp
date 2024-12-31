#pragma once

#include <glm/glm.hpp>

#include "universe/renderer/texture.hpp"

namespace Universe
{
    class Animation
    {
    public:
        Animation(Ref<TextureAtlas> textureAtlas, float frameDuration, bool loop)
        {
            m_TextureAtlas = textureAtlas;
            m_StartFrame = 0;
            m_EndFrame = textureAtlas->GetRows() * textureAtlas->GetColumns() - 1;
            m_CurrentFrame = 0;
            m_FrameDuration = frameDuration;
            m_Loop = loop;
        }

        void Update(Timestep ts);

        std::array<glm::vec2, 4> GetCurrentFrameTextureCoords() const { return m_TextureAtlas->CalculateTextureCoords(m_CurrentFrame); }

        void SetStartFrame(uint32_t startFrame) { m_StartFrame = startFrame; }
        void SetEndFrame(uint32_t endFrame) { m_EndFrame = endFrame; }

        Ref<Texture2D> GetTexture() const { return m_TextureAtlas->GetTexture(); }

        static Ref<Animation> Create(Ref<TextureAtlas> textureAtlas, float frameDuration, bool loop);

    private:
        Ref<TextureAtlas> m_TextureAtlas;
        uint32_t m_StartFrame, m_EndFrame, m_CurrentFrame;
        float m_FrameDuration, m_Timer = 0.0f;
        bool m_Loop;
    };
}