#include "universe.hpp"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

class ExampleLayer2D : public Universe::Layer
{
public:
    ExampleLayer2D() : m_CameraController(1280.0f / 720.0f) {}

    void OnAttach() override
    {
        // m_GrassTile = Universe::Texture2D::Create("../../sandbox/assets/textures/grass.png");
        // m_Player = Universe::Texture2D::Create("../../sandbox/assets/textures/player.png");
    }

    void OnDetach() override {}

    void OnUpdate(Universe::Timestep ts) override
    {
        // Update
        m_CameraController.OnUpdate(ts);

        // Player movement

        if (Universe::Input::IsKeyPressed(UE_KEY_LEFT_CONTROL)) {
            m_PlayerSpeedX = m_PlayerRunningSpeed;
        }
        else {
            m_PlayerSpeedX = 3.0f;
        }

        if (Universe::Input::IsKeyPressed(UE_KEY_A) && Universe::Input::IsKeyPressed(UE_KEY_D)) {}
        else if (Universe::Input::IsKeyPressed(UE_KEY_A)) {
            m_PlayerPosition.x -= m_PlayerSpeedX * ts;
        }
        else if (Universe::Input::IsKeyPressed(UE_KEY_D)) {
            m_PlayerPosition.x += m_PlayerSpeedX * ts;
        }

        if (Universe::Input::IsKeyPressed(UE_KEY_SPACE) && !m_IsJumping) {
            m_IsJumping = true;
            m_PlayerSpeedY = 3.0f;
        }

        if (m_IsJumping) {
            m_PlayerPosition.y += m_PlayerSpeedY * ts;
            m_PlayerSpeedY -= m_Gravity * ts;
            if (m_PlayerPosition.y < -2.5f) {
                m_PlayerPosition.y = -2.5f;
                m_IsJumping = false;
            }
        }

        // Render
        Universe::Renderer2D::BeginScene(m_CameraController.getCamera());
        // Universe::Renderer2D::DrawQuad( m_PlayerPosition, { 1.0f, 2.0f }, m_Player);
        Universe::Renderer2D::DrawQuad({ m_PlayerPosition.x, -2.5f }, { 1.0f, 2.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });

        // Dirt tiles
        // for (float x = -100.0f; x < 100.0f; x += 1.0f)
        // {
        //     Universe::Renderer2D::DrawQuad({ x, -4.0f }, { 1.0f, 1.0f }, m_GrassTile);
        //     Universe::Renderer2D::DrawQuad({ x, -5.0f }, { 1.0f, 1.0f }, m_DirtTile);
        // }

        glm::vec3 camera_following_the_player = { m_PlayerPosition.x, 0.0f, 0.0f };

        m_CameraController.getCamera().SetPosition(camera_following_the_player);
    }

    void OnEvent(Universe::Event& e) override
    {
        m_CameraController.OnEvent(e);
    }

    void OnImGuiRender() override
    {
        // Controll player speed
        ImGui::Begin("Player Speed");
        ImGui::SliderFloat("Player Speed X", &m_PlayerSpeedX, 0.0f, 10.0f);
        ImGui::SliderFloat("Player Speed Y", &m_PlayerSpeedY, 0.0f, 10.0f);
        ImGui::SliderFloat("Gravity", &m_Gravity, 0.0f, 10.0f);
        ImGui::End();
    }

private:
    Universe::OrthographicCameraController m_CameraController;
    Universe::Ref<Universe::Texture2D> m_GrassTile;
    Universe::Ref<Universe::Texture2D> m_DirtTile;
    Universe::Ref<Universe::Texture2D> m_Player;
    glm::vec2 m_PlayerPosition = { 0.0f, -2.5f };
    float m_PlayerSpeedX = 3.0f;
    float m_PlayerRunningSpeed = 5.0f;
    float m_PlayerSpeedY = 0.0f;
    float m_Gravity = 8.0f;
    bool m_IsJumping = false;
};

class Sandbox : public Universe::Application
{
public:
    Sandbox()
    {
        // PushLayer(new ExampleLayer());
        PushLayer(new ExampleLayer2D());
    }
};

Universe::Application* Universe::CreateApplication()
{
    return new Sandbox();
}
