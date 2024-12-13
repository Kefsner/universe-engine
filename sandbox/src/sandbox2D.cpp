#include "pch.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "sandbox2D.hpp"

Sandbox2D::Sandbox2D() : m_CameraController(1920.0f / 1080.0f) {}

void Sandbox2D::OnAttach()
{
    Universe::RenderCommand::SetClearColor({0.8f, 0.2f, 0.3f, 1.0f}); // Set the clear color to pink

    m_GrassTexture = Universe::Texture2D::Create("sandbox/assets/textures/grass.png");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Universe::Timestep ts)
{
    m_CameraController.OnUpdate(ts);

    Universe::RenderCommand::Clear();

    Universe::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Universe::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_Color);
    Universe::Renderer2D::DrawQuad({1.0f, 0.0f}, {2.0f, 2.0f}, m_GrassTexture, 1.0f, m_Color);
    Universe::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Color Picker");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_Color));
    ImGui::End();
}

void Sandbox2D::OnEvent(Universe::Event& e)
{
    m_CameraController.OnEvent(e);
}
