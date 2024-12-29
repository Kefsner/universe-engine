#include "sandbox2D.hpp"

void Sandbox2D::OnAttach()
{
    Universe::Renderer2D::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

    m_Camera = Universe::OrthographicCamera(16.0f, 9.0f);
    m_Camera.AttachDefaultController(); // WASD controller
    m_checkerboard = Universe::Texture2D::Create("sandbox/assets/textures/checkerboard.png");
    m_PlayerSpriteSheetTexture = Universe::Texture2D::Create("sandbox/assets/textures/player_sheet.png");
    m_PlayerSpriteSheet = Universe::SpriteSheet::Create(m_PlayerSpriteSheetTexture, 1, 8);
    m_IdleAnimation = Universe::Animation::Create(m_PlayerSpriteSheet, 0, 3, 0.1f, true);
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Universe::Timestep ts)
{
    m_Camera.OnUpdate(ts);

    m_IdleAnimation->Update(ts);

    Universe::Renderer2D::BeginScene(m_Camera);
    Universe::Renderer2D::DrawAnimatedQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_IdleAnimation);
    Universe::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Universe::Event& event)
{
    m_Camera.OnEvent(event);
}
