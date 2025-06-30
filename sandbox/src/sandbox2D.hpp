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
    Universe::Ref<Universe::Animation> m_IdleAnimation;
    Universe::Ref<Universe::Animation> m_RunningAnimation;
    Universe::Ref<Universe::Animation> m_CurrentAnimation;

    bool m_FacingRight = true;
    bool m_FreeCamera = false;

    glm::vec3 m_PlayerPosition = { 0.0f, 0.0f, 0.0f };
    float m_MoveSpeed = 2.5f;
    float m_RunningSpeed = 5.0f;

    Universe::Ref<Universe::World> m_World;
};