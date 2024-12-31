#include "sandbox2D.hpp"

void Sandbox2D::OnAttach()
{
    Universe::Renderer2D::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

    m_Camera = Universe::OrthographicCamera(16.0f, 9.0f);
    m_Camera.AttachDefaultController(); // WASD controller

    // Animation Pipeline

    // Idle Animation
    Universe::Ref<Universe::Texture2D> texture;
    texture = Universe::Texture2D::Create("sandbox/assets/textures/animations/player_idle.png");
    Universe::Ref<Universe::TextureAtlas> textureAtlas;
    textureAtlas = Universe::TextureAtlas::Create(texture, 1, 9);
    m_IdleAnimation = Universe::Animation::Create(textureAtlas, 0.1f, true);

    // Running Animation
    texture = Universe::Texture2D::Create("sandbox/assets/textures/animations/player_running.png");
    textureAtlas = Universe::TextureAtlas::Create(texture, 1, 8);
    m_RunningAnimation = Universe::Animation::Create(textureAtlas, 0.1f, true);
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Universe::Timestep ts)
{
    m_Camera.OnUpdate(ts);

    Universe::Ref<Universe::Animation> current_animation;
    
    current_animation = m_IdleAnimation;
    
    if (Universe::Input::IsKeyPressed(Universe::Key::Space))
        current_animation = m_RunningAnimation;

    current_animation->Update(ts);

    Universe::Renderer2D::BeginScene(m_Camera);
    Universe::Renderer2D::DrawAnimatedQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, current_animation);
    Universe::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Universe::Event& event)
{
    m_Camera.OnEvent(event);
}
