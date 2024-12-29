#include "sandbox2D.hpp"

void Sandbox2D::OnAttach()
{
    Universe::Renderer2D::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

    m_Camera = Universe::OrthographicCamera(16.0f, 9.0f);
    m_Camera.AttachDefaultController();
    m_checkerboard = Universe::Texture2D::Create("sandbox/assets/textures/checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Universe::Timestep ts)
{
    m_Camera.OnUpdate(ts);
    
    Universe::Renderer2D::BeginScene(m_Camera);
    Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f }, m_checkerboard);
    Universe::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Universe::Event& event)
{
    m_Camera.OnEvent(event);
}
