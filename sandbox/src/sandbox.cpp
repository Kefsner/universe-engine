#include "universe.hpp"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include "engine/renderer/opengl/opengl_shader.hpp"

class ExampleLayer2D : public Universe::Layer
{
public:
    ExampleLayer2D() : m_CameraController(1280.0f / 720.0f) {}

    void OnAttach() override {
        // Vertices
        float vertices[4*2] = {
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f,
            -0.5f, -0.5f
        };

        // Vertex Buffer
        Universe::Ref<Universe::VertexBuffer> VertexBuffer;
        VertexBuffer = Universe::VertexBuffer::Create(vertices, sizeof(vertices));
        Universe::BufferLayout layout = {
            { Universe::ShaderDataType::Float2, "a_Position" }
        };
        VertexBuffer->SetLayout(layout);

        // Index Buffer
        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        Universe::Ref<Universe::IndexBuffer> IndexBuffer;
        IndexBuffer = Universe::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        // Vertex Array
        m_VertexArray = Universe::VertexArray::Create();
        m_VertexArray->AddVertexBuffer(VertexBuffer);
        m_VertexArray->SetIndexBuffer(IndexBuffer);

        // Shader
        m_Shader = Universe::Shader::Create("../../sandbox/assets/shaders/square.glsl");
    }

    void OnDetach() override {
    }

    void OnUpdate(Universe::Timestep ts) override {
        // Update
        m_CameraController.OnUpdate(ts);

        // Render
        Universe::Renderer::BeginScene(m_CameraController.getCamera());
        std::dynamic_pointer_cast<Universe::OpenGLShader>(m_Shader)->Bind();
        std::dynamic_pointer_cast<Universe::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_ImGuiColor);
        Universe::Renderer::Submit(m_Shader, m_VertexArray);
        Universe::Renderer::EndScene();
    }

    void OnEvent(Universe::Event& e) override {
        m_CameraController.OnEvent(e);
    }

    void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Square Color", glm::value_ptr(m_ImGuiColor));
        ImGui::End();
    }

private:
    Universe::OrthographicCameraController m_CameraController;
    Universe::Ref<Universe::VertexArray> m_VertexArray;
    Universe::Ref<Universe::Shader> m_Shader;

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
