#include "universe.hpp"
#include <glm/gtc/matrix_transform.hpp>
class ExampleLayer : public Universe::Layer
{
public:
    ExampleLayer() : m_CameraController(1280.0f / 720.0f)
    {
        // // Square vertices
        float vertices[] = {
            0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f , 0.0f, 0.0f
            };

        // Triangle indices
        uint32_t indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        // Create vertex buffer
        m_VertexBuffer = Universe::VertexBuffer::Create(vertices, sizeof(vertices));
        {
            Universe::BufferLayout layout = {
                { Universe::ShaderDataType::Float2, "a_Position" },
                { Universe::ShaderDataType::Float2, "a_TexCoord" }
            };
            m_VertexBuffer->SetLayout(layout);
        }

        // Create index buffer
        m_IndexBuffer = Universe::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        // Create vertex array
        m_VertexArray = Universe::VertexArray::Create();
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        // Create shader
        m_Shader = Universe::Shader::Create("../../sandbox/assets/shaders/texture.glsl");

        // Create texture
        m_Texture = Universe::Texture2D::Create("../../sandbox/assets/textures/checkerboard_texture_rgb.png");
        m_LogoTexture = Universe::Texture2D::Create("../../sandbox/assets/textures/logo.png");

    }

    void OnUpdate(Universe::Timestep ts) override {
        m_CameraController.OnUpdate(ts);
    
        Universe::Renderer::BeginScene(m_CameraController.getCamera());
        m_Texture->Bind();
        Universe::Renderer::Submit(m_Shader, m_VertexArray, glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f)));
        m_LogoTexture->Bind();
        Universe::Renderer::Submit(m_Shader, m_VertexArray);
        Universe::Renderer::EndScene();
    }

    void OnEvent(Universe::Event& event) override
    {
        m_CameraController.OnEvent(event);
    }

private:
    Universe::OrthographicCameraController m_CameraController;
    Universe::Ref<Universe::VertexBuffer> m_VertexBuffer;
    Universe::Ref<Universe::IndexBuffer> m_IndexBuffer;
    Universe::Ref<Universe::VertexArray> m_VertexArray;
    Universe::Ref<Universe::Texture2D> m_Texture;
    Universe::Ref<Universe::Texture2D> m_LogoTexture;
    Universe::Ref<Universe::Shader> m_Shader;
    Universe::ShaderLibrary m_ShaderLibrary;
};

class Sandbox : public Universe::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }
};

Universe::Application* Universe::CreateApplication()
{
    return new Sandbox();
}
