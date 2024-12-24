#include "pch.hpp"

#include "renderer2D_quad.hpp"

void Renderer2DQuad::OnAttach()
{
    Universe::Renderer2D::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
}

void Renderer2DQuad::OnDetach()
{
    Universe::Renderer2D::Shutdown();
}

void Renderer2DQuad::OnUpdate(Universe::Timestep ts)
{
    Universe::Renderer2D::BeginScene();
    Universe::Renderer2D::DrawQuad();
    Universe::Renderer2D::EndScene();
}

void Renderer2DQuad::OnEvent(Universe::Event& event)
{
    UE_CORE_TRACE("{0}", event.ToString());
}