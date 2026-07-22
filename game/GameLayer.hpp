#pragma once

#include <universe.hpp>

#include "world/Block.hpp"

#include <glm/glm.hpp>

namespace Universe
{
    class GameLayer : public Layer
    {
    public:
        GameLayer();
        ~GameLayer() = default;

        void OnUpdate() override;
    
    private:
        void RenderBlock(Block block, glm::vec3 position);

    private:
        std::shared_ptr<TextureAtlas> m_BlockTextureAtlas;
        std::unique_ptr<Camera> m_Camera;

        float m_Yaw = -90.0f;
        float m_Pitch = 0.0f;

        float m_LastMouseXPos = 0.0f;
        float m_LastMouseYPos = 0.0f;

        bool m_CursorDisabled;
    };
}