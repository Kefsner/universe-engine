#include "universe.hpp"
#include <glm/gtc/matrix_transform.hpp>
class ExampleLayer : public Universe::Layer
{
public:
    ExampleLayer() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)
    {
        // Square vertices
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
        if (Universe::Input::IsKeyPressed(UE_KEY_A) && Universe::Input::IsKeyPressed(UE_KEY_D)) {}
        else if (Universe::Input::IsKeyPressed(UE_KEY_A)) {
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        }
        else if (Universe::Input::IsKeyPressed(UE_KEY_D)) {
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        }

        if (Universe::Input::IsKeyPressed(UE_KEY_W) && Universe::Input::IsKeyPressed(UE_KEY_S)) {}
        else if (Universe::Input::IsKeyPressed(UE_KEY_W)) {
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        }
        else if (Universe::Input::IsKeyPressed(UE_KEY_S)) {
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        }
        
        m_Camera.SetPosition(m_CameraPosition);

        Universe::Renderer::BeginScene(m_Camera);
        m_Texture->Bind();
        Universe::Renderer::Submit(m_Shader, m_VertexArray, glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f)));
        m_LogoTexture->Bind();
        Universe::Renderer::Submit(m_Shader, m_VertexArray);
        Universe::Renderer::EndScene();
    }

    void OnEvent(Universe::Event& event) override
    {
    }

private:
    Universe::Ref<Universe::VertexBuffer> m_VertexBuffer;
    Universe::Ref<Universe::IndexBuffer> m_IndexBuffer;
    Universe::Ref<Universe::VertexArray> m_VertexArray;
    Universe::Ref<Universe::Texture2D> m_Texture;
    Universe::Ref<Universe::Texture2D> m_LogoTexture;
    Universe::Ref<Universe::Shader> m_Shader;
    Universe::ShaderLibrary m_ShaderLibrary;
    Universe::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 0.1f;

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
