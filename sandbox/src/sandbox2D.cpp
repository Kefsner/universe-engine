#include "sandbox2D.hpp"

void Sandbox2D::OnAttach()
{
    m_Camera = Universe::OrthographicCamera(32.0f, 18.0f);
    m_Camera.AttachDefaultController(); // WASD controller

    m_Scene = Universe::Scene::Create();

    m_Player = m_Scene->CreateEntity("Player");

    auto& assetManager = Universe::AssetManager::GetInstance();

    auto idleAnim = assetManager.LoadAnimation(
        "sandbox/assets/textures/animations/player_idle.png",
        1, 9, 0.1f, true
    );

    // Running Animation
    auto runningAnim = assetManager.LoadAnimation(
        "sandbox/assets/textures/animations/player_running.png",
        1, 8, 0.1f, true
    );

    auto& animator = m_Player.AddComponent<Universe::AnimatorComponent>();
    animator.AddAnimation("Idle", idleAnim);
    animator.AddAnimation("Running", runningAnim);

    // === World Generation ===
    m_World = Universe::World::Create();
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Universe::Timestep ts)
{
    m_Camera.OnUpdate(ts);

    auto& transform = m_Player.GetComponent<Universe::TransformComponent>();
    auto& animator = m_Player.GetComponent<Universe::AnimatorComponent>();

    float speed = Universe::Input::IsKeyPressed(Universe::Key::LeftShift) ? m_RunningSpeed : m_MoveSpeed;

    bool isMoving = false;

    if (Universe::Input::IsKeyPressed(Universe::Key::Right) && !Universe::Input::IsKeyPressed(Universe::Key::Left))
    {
        transform.position.x += ts * speed;
        m_FacingRight = true;
        isMoving = true;
    }
    if (Universe::Input::IsKeyPressed(Universe::Key::Left) && !Universe::Input::IsKeyPressed(Universe::Key::Right))
    {
        transform.position.x -= ts * speed;
        m_FacingRight = false;
        isMoving = true;
    }
    if (Universe::Input::IsKeyPressed(Universe::Key::Up) && !Universe::Input::IsKeyPressed(Universe::Key::Down))
    {
        transform.position.y += ts * speed;
        isMoving = true;
    }
    if (Universe::Input::IsKeyPressed(Universe::Key::Down) && !Universe::Input::IsKeyPressed(Universe::Key::Up))
    {
        transform.position.y -= ts * speed;
        isMoving = true;
    }
    const std::string currentAnimation = isMoving ? "Running" : "Idle";
    if (animator.GetCurrentName() != currentAnimation)
        animator.SetCurrentAnimation(currentAnimation);

    animator.Update(ts);

    glm::vec2 scale = m_FacingRight ? glm::vec2(6.0f, 6.0f) : glm::vec2(-6.0f, 6.0f);

    Universe::Renderer2D::BeginScene(m_Camera);
    m_World->Render();

    Universe::Renderer2D::DrawAnimatedQuad(transform.position, scale, { 1.0f, 1.0f, 1.0f, 1.0f }, animator.GetCurrentAnimation(), animator.GetCurrentFrame());
    Universe::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Universe::Event& event)
{
    m_Camera.OnEvent(event);
}
