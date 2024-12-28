#pragma once

#include <universe.hpp>

class Sandbox2D : public Universe::Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;

    bool OnKeyPressed(Universe::KeyPressedEvent& event);

private:
    Universe::Ref<Universe::Texture2D> m_BackgroundTexture;
    Universe::Ref<Universe::Texture2D> m_StartButtonTexture;
    Universe::Ref<Universe::Texture2D> m_ExitButtonTexture;

    bool m_GameIsRunning = false;
    bool m_StartButtonSelected = true;
};