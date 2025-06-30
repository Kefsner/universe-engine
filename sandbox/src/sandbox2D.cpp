#include "sandbox2D.hpp"

void Sandbox2D::OnAttach()
{
    Universe::Renderer2D::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

    m_Camera = Universe::OrthographicCamera(32.0f, 18.0f);
    m_Camera.AttachDefaultController(); // WASD controller

    // === Animation Pipeline ===
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

    // === World Generation ===
    m_World = Universe::World::Create();
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Universe::Timestep ts)
{
    m_Camera.OnUpdate(ts);

    m_CurrentAnimation = m_IdleAnimation;

    float speed = m_MoveSpeed;
    if (Universe::Input::IsKeyPressed(Universe::Key::LeftShift))
        speed = m_RunningSpeed;

    if (Universe::Input::IsKeyPressed(Universe::Key::Right) && !Universe::Input::IsKeyPressed(Universe::Key::Left))
    {
        m_PlayerPosition.x += ts * speed;
        m_CurrentAnimation = m_RunningAnimation;
        m_FacingRight = true;
    }
    if (Universe::Input::IsKeyPressed(Universe::Key::Left) && !Universe::Input::IsKeyPressed(Universe::Key::Right))
    {
        m_PlayerPosition.x -= ts * speed;
        m_CurrentAnimation = m_RunningAnimation;
        m_FacingRight = false;
    }
    if (Universe::Input::IsKeyPressed(Universe::Key::Up) && !Universe::Input::IsKeyPressed(Universe::Key::Down))
    {
        m_PlayerPosition.y += ts * speed;
        m_CurrentAnimation = m_RunningAnimation;
    }
    if (Universe::Input::IsKeyPressed(Universe::Key::Down) && !Universe::Input::IsKeyPressed(Universe::Key::Up))
    {  
        m_PlayerPosition.y -= ts * speed;
        m_CurrentAnimation = m_RunningAnimation;
    }

    m_CurrentAnimation->Update(ts);

    if (!m_FreeCamera)
        m_Camera.SetPosition(m_PlayerPosition); // Overwrite defaultcontroller.Could add a button to detach this call and move camera freely and after release it will return to player position.

    UE_TRACE("Player Position: ({}, {})", m_PlayerPosition.x, m_PlayerPosition.y);

    glm::vec2 scale = { 6.0f, 6.0f };
    if (!m_FacingRight)
    {
        scale.x = -6.0f;
    }

    Universe::Renderer2D::BeginScene(m_Camera);
    m_World->Render();
    Universe::Renderer2D::DrawAnimatedQuad(m_PlayerPosition, scale, { 1.0f, 1.0f, 1.0f, 1.0f }, m_CurrentAnimation);
    Universe::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Universe::Event& event)
{
    m_Camera.OnEvent(event);

    Universe::EventDispatcher dispatcher(event);

    dispatcher.Dispatch<Universe::KeyReleasedEvent>([&](Universe::KeyReleasedEvent& e)
    {
        if (e.GetKeyCode() == Universe::Key::Tab)
        {
            m_FreeCamera = !m_FreeCamera;
            return true;
        }
        return false;
    });
}

void Sandbox2D::OnImGuiRender()
{
    // ImGui::Begin("Settings");
    // ImGui::Checkbox("Free Camera", &m_FreeCamera);
    // ImGui::End();
}
