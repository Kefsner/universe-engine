#include "pch.hpp"

#include <glm/glm.hpp>

#include "universe/base/timestep.hpp"
#include "universe/renderer/animation.hpp"

namespace Universe
{
    Ref<Animation> Animation::Create(Ref<TextureAtlas> textureAtlas, float frameDuration, bool loop)
    {
        return CreateRef<Animation>(textureAtlas, frameDuration, loop);
    }


    void Animation::Update(Timestep ts)
    {
        m_Timer += ts;
        if (m_Timer >= m_FrameDuration)
        {
            m_Timer = 0.0f;
            m_CurrentFrame++;
            if (m_CurrentFrame > m_EndFrame)
            {
                if (m_Loop)
                    m_CurrentFrame = m_StartFrame;
                else
                    m_CurrentFrame = m_EndFrame;
            }
        }
    }
}