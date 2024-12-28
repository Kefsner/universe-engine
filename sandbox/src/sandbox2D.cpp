#include "sandbox2D.hpp"

void Sandbox2D::OnAttach()
{
    Universe::Renderer2D::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

    m_Texture = Universe::Texture2D::Create("sandbox/assets/textures/main.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Universe::Timestep ts)
{
    Universe::Renderer2D::BeginScene();
    if (Universe::Input::IsKeyPressed(Universe::Key::Space))
        Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
    else
        Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_Texture);
    Universe::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Universe::Event& event)
{
    UE_CORE_TRACE("{0}", event.ToString());
}