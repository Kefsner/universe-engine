#pragma once

#include <universe.hpp>

class Sandbox2D : public Universe::Layer
{
public:
    Sandbox2D()
        : m_AssetManager(Universe::AssetManager::GetInstance()) {}
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;

private:
    Universe::OrthographicCamera m_Camera;
    Universe::Ref<Universe::World> m_World;
    Universe::Ref<Universe::Scene> m_Scene;

    Universe::AssetManager& m_AssetManager;
    
    Universe::Entity m_Player;
    float m_MoveSpeed = 5.0f;
    float m_RunningSpeed = 10.0f;
    bool m_FacingRight = true;

    Universe::Entity m_Rock;
};