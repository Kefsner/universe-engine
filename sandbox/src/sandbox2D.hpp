#pragma once

#include <universe.hpp>

class Sandbox2D : public Universe::Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;
private:
    Universe::OrthographicCamera m_Camera;
    Universe::Ref<Universe::Texture2D> m_checkerboard;
    Universe::Ref<Universe::Texture2D> m_PlayerSpriteSheetTexture;
    Universe::Ref<Universe::TextureAtlas> m_PlayerSpriteSheet;
    Universe::Ref<Universe::Animation> m_IdleAnimation;

};