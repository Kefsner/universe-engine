#include "universe.hpp"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

class ExampleLayer2D : public Universe::Layer
{
public:
    ExampleLayer2D() : m_CameraController(1280.0f / 720.0f) {}

    void OnAttach() override
    {
        m_GrassTile = Universe::Texture2D::Create("../../sandbox/assets/textures/grass.png");
        m_Player = Universe::Texture2D::Create("../../sandbox/assets/textures/player.png");
    }

    void OnDetach() override {}

    void OnUpdate(Universe::Timestep ts) override
    {
        // Update
        m_CameraController.OnUpdate(ts);

        // Render
        Universe::Renderer2D::BeginScene(m_CameraController.getCamera());
        Universe::Renderer2D::DrawQuad({  0.0f,  0.1f }, { 2.0f, 2.0f }, m_Player);
        Universe::Renderer2D::DrawQuad({ -3.0f, -0.5f }, { 1.0f, 1.0f }, m_GrassTile);
        Universe::Renderer2D::DrawQuad({ -2.0f, -0.5f }, { 1.0f, 1.0f }, m_GrassTile);
        Universe::Renderer2D::DrawQuad({ -1.0f, -0.5f }, { 1.0f, 1.0f }, m_GrassTile);
        Universe::Renderer2D::DrawQuad({  0.0f, -0.5f }, { 1.0f, 1.0f }, m_GrassTile);
        Universe::Renderer2D::DrawQuad({  1.0f, -0.5f }, { 1.0f, 1.0f }, m_GrassTile);
        Universe::Renderer2D::DrawQuad({  2.0f, -0.5f }, { 1.0f, 1.0f }, m_GrassTile);
        Universe::Renderer2D::DrawQuad({  3.0f, -0.5f }, { 1.0f, 1.0f }, m_GrassTile);
        Universe::Renderer2D::EndScene();
    }

    void OnEvent(Universe::Event& e) override
    {
        m_CameraController.OnEvent(e);
    }

    void OnImGuiRender() override
    {
    }

private:
    Universe::OrthographicCameraController m_CameraController;
    Universe::Ref<Universe::Texture2D> m_GrassTile;
    Universe::Ref<Universe::Texture2D> m_Player;
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
