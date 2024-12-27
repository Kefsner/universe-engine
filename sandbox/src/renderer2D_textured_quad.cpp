#include "renderer2D_textured_quad.hpp"

void Renderer2DTexturedQuad::OnAttach()
{
    Universe::Renderer2D::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

    m_Texture = Universe::Texture2D::Create("sandbox/assets/textures/checkerboard.png");
}

void Renderer2DTexturedQuad::OnDetach()
{
}

void Renderer2DTexturedQuad::OnUpdate(Universe::Timestep ts)
{
    Universe::Renderer2D::BeginScene();
    Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 0.9f }, m_Texture);
    Universe::Renderer2D::EndScene();
}

void Renderer2DTexturedQuad::OnEvent(Universe::Event& event)
{
    UE_CORE_TRACE("{0}", event.ToString());
}