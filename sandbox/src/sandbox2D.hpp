
#pragma once

#include <imgui.h>
#include <glm/glm.hpp>

#include "universe.hpp"

class Sandbox2D : public Universe::Layer
{
public:
    Sandbox2D();
    
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(Universe::Timestep ts) override;
    void OnEvent(Universe::Event& e) override;
    void OnImGuiRender() override;

private:
    Universe::OrthographicCameraController m_CameraController;
    Universe::Ref<Universe::Texture2D> m_GrassTexture;
    glm::vec4 m_Color = { 0.2f, 0.3f, 0.8f, 1.0f };
};
