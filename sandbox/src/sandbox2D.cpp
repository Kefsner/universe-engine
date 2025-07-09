#include "sandbox2D.hpp"

void Sandbox2D::OnAttach()
{
    m_Camera = Universe::OrthographicCamera(32.0f, 18.0f);
    m_Camera.AttachDefaultController(); // WASD controller

    m_Scene = Universe::Scene::Create();

    m_Player = m_Scene->CreateEntity("Player");
    m_Player.AddComponent<Universe::AABBComponent>(glm::vec2(1.0f, 1.0f));

    m_Rock = m_Scene->CreateEntity("Rock", glm::vec3(5.0f, 0.0f, 0.0f));
    m_Rock.AddComponent<Universe::AABBComponent>(glm::vec2(1.0f, 1.0f));

    auto rockTexture = m_AssetManager.LoadTexture("sandbox/assets/textures/rock.png");

    m_Rock.AddComponent<Universe::SpriteRendererComponent>(rockTexture);

    auto idleAnim = m_AssetManager.LoadAnimation(
        "sandbox/assets/textures/animations/player_idle.png",
        1, 9, 0.1f, true
    );

    // Running Animation
    auto runningAnim = m_AssetManager.LoadAnimation(
        "sandbox/assets/textures/animations/player_running.png",
        1, 8, 0.1f, true
    );

    auto& animator = m_Player.AddComponent<Universe::AnimatorComponent>();
    animator.AddAnimation("Idle", idleAnim);
    animator.AddAnimation("Running", runningAnim);

    // === World Generation ===
    // m_World = Universe::World::Create();
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

    glm::vec3 proposedPosition = transform.position;

    if (Universe::Input::IsKeyPressed(Universe::Key::Right) && !Universe::Input::IsKeyPressed(Universe::Key::Left))
    {
        proposedPosition.x += ts * speed;
        m_FacingRight = true;
        isMoving = true;
    }
    if (Universe::Input::IsKeyPressed(Universe::Key::Left) && !Universe::Input::IsKeyPressed(Universe::Key::Right))
    {
        proposedPosition.x -= ts * speed;
        m_FacingRight = false;
        isMoving = true;
    }
    if (Universe::Input::IsKeyPressed(Universe::Key::Up) && !Universe::Input::IsKeyPressed(Universe::Key::Down))
    {
        proposedPosition.y += ts * speed;
        isMoving = true;
    }
    if (Universe::Input::IsKeyPressed(Universe::Key::Down) && !Universe::Input::IsKeyPressed(Universe::Key::Up))
    {
        proposedPosition.y -= ts * speed;
        isMoving = true;
    }
    const std::string currentAnimation = isMoving ? "Running" : "Idle";
    if (animator.GetCurrentName() != currentAnimation)
        animator.SetCurrentAnimation(currentAnimation);

    animator.Update(ts);

    glm::vec2 scale = m_FacingRight ? glm::vec2(6.0f, 6.0f) : glm::vec2(-6.0f, 6.0f);

    auto& aabbPlayer = m_Player.GetComponent<Universe::AABBComponent>();

    auto& rockTransform = m_Rock.GetComponent<Universe::TransformComponent>();
    auto& aabbRock = m_Rock.GetComponent<Universe::AABBComponent>();

    // Only move if no collision
    if (!Universe::Collision::AABBvsAABB(proposedPosition, aabbPlayer.size, rockTransform.position, aabbRock.size))
    {
        transform.position = proposedPosition;
    }
    else
    {
        UE_CORE_INFO("Blocked by rock!");
    }

    Universe::Renderer2D::BeginScene(m_Camera);
    // m_World->Render();
    Universe::Renderer2D::DrawAnimatedQuad(transform.position, scale, { 1.0f, 1.0f, 1.0f, 1.0f }, animator.GetCurrentAnimation(), animator.GetCurrentFrame());
    Universe::Renderer2D::DrawQuad(rockTransform.position, aabbRock.size, { 1.0f, 1.0f, 1.0f, 1.0f }, m_Rock.GetComponent<Universe::SpriteRendererComponent>().texture);
    Universe::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Universe::Event& event)
{
    m_Camera.OnEvent(event);
}
