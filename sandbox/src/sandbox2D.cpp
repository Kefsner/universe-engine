#include "sandbox2D.hpp"

void Sandbox2D::OnAttach()
{
    Universe::Renderer2D::Init();
}

void Sandbox2D::OnDetach()
{
    Universe::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(Universe::Timestep ts)
{
    Universe::Renderer2D::BeginScene();
    Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Universe::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Universe::Event& event)
{
}
