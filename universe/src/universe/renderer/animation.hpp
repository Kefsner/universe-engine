#pragma once

#include <glm/glm.hpp>

#include "universe/renderer/spritesheet.hpp"

namespace Universe
{
    class Animation
    {
    public:
        Animation(Ref<SpriteSheet> spriteSheet, uint32_t startFrame, uint32_t endFrame, float frameDuration, bool loop = true)
            : m_SpriteSheet(spriteSheet), m_StartFrame(startFrame), m_EndFrame(endFrame), m_FrameDuration(frameDuration), m_Loop(loop)
        {
            m_CurrentFrame = startFrame;
        }

        void Update(Timestep ts); 

        Ref<Texture2D> GetTexture() const { return m_SpriteSheet->GetTexture(); }
        std::array<glm::vec2, 4> GetTextureCoords() const { return m_SpriteSheet->GetTextureCoords(m_CurrentFrame); }

        static Ref<Animation> Create(Ref<SpriteSheet> spriteSheet, uint32_t startFrame, uint32_t endFrame, float frameDuration, bool loop = true)
        {
            return CreateRef<Animation>(spriteSheet, startFrame, endFrame, frameDuration, loop);
        }

    private:
        Ref<SpriteSheet> m_SpriteSheet;
        uint32_t m_StartFrame, m_EndFrame, m_CurrentFrame;
        float m_FrameDuration, m_Timer = 0.0f;
        bool m_Loop;
    };
}