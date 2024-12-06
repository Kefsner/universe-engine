#include "universe.hpp"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

class ExampleLayer2D : public Universe::Layer
{
public:
    ExampleLayer2D() : m_CameraController(1280.0f / 720.0f) {}

    void OnAttach() override
    {
        m_CheckerboardTexture = Universe::Texture2D::Create("../../sandbox/assets/textures/checkerboard_texture_rgb.png");
    }

    void OnDetach() override {}

    void OnUpdate(Universe::Timestep ts) override
    {
        // Update
        m_CameraController.OnUpdate(ts);

        // Render
        Universe::Renderer2D::BeginScene(m_CameraController.getCamera());
        Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_ImGuiColor);
        Universe::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });
        Universe::Renderer2D::DrawQuad({ 0.0f, 1.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture);
        Universe::Renderer2D::EndScene();
    }

    void OnEvent(Universe::Event& e) override
    {
        m_CameraController.OnEvent(e);
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Square Color", glm::value_ptr(m_ImGuiColor));
        ImGui::End();
    }

private:
    Universe::OrthographicCameraController m_CameraController;
    Universe::Ref<Universe::Texture2D> m_CheckerboardTexture;
    glm::vec4 m_ImGuiColor = { 0.2f, 0.3f, 0.8f, 1.0f };
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
