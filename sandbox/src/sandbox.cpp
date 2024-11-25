#include "universe.hpp"

class ExampleLayer : public Universe::Layer
{
public:
    ExampleLayer() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)
    {
        // Vertex data for a cube
        float vertices[] = {
            // Position         // Color (R, G, B)
            // Front face
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, // Bottom-left (red)
             0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, // Bottom-right (green)
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // Top-right (blue)
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // Top-left (yellow)

            // Back face
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, // Bottom-left (magenta)
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, // Bottom-right (cyan)
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, // Top-right (white)
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f  // Top-left (black)
        };

        // Index data for a cube (12 triangles, 2 per face)
        uint32_t indices[] = {
            // Front face
            0, 1, 2,
            2, 3, 0,

            // Back face
            4, 5, 6,
            6, 7, 4,

            // Left face
            4, 0, 3,
            3, 7, 4,

            // Right face
            1, 5, 6,
            6, 2, 1,

            // Top face
            3, 2, 6,
            6, 7, 3,

            // Bottom face
            4, 5, 1,
            1, 0, 4
        };

        // Create vertex buffer
        m_VertexBuffer = Universe::VertexBuffer::Create(vertices, sizeof(vertices));
        {
            Universe::BufferLayout layout = {
                { Universe::ShaderDataType::Float3, "a_Position" },
                { Universe::ShaderDataType::Float3, "a_Color" }
            };
            m_VertexBuffer->SetLayout(layout);
        }

        // Create index buffer
        m_IndexBuffer = Universe::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        // Create vertex array
        m_VertexArray = Universe::VertexArray::Create();
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        // Shader source code
        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec3 a_Color;

            uniform mat4 u_ViewProjection;

            out vec3 v_Color;

            void main()
            {
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            in vec3 v_Color;
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(v_Color, 1.0);
            }
        )";

        // Create shader
        m_Shader = Universe::Shader::Create(vertexSrc, fragmentSrc);

    }

    void OnUpdate() override
    {
        if (Universe::Input::IsKeyPressed(UE_KEY_A))
            m_CameraPosition.x -= m_CameraMoveSpeed;
        else if (Universe::Input::IsKeyPressed(UE_KEY_D))
            m_CameraPosition.x += m_CameraMoveSpeed;
        if (Universe::Input::IsKeyPressed(UE_KEY_W))
            m_CameraPosition.y += m_CameraMoveSpeed;
        else if (Universe::Input::IsKeyPressed(UE_KEY_S))
            m_CameraPosition.y -= m_CameraMoveSpeed;

        m_Camera.SetPosition(m_CameraPosition);

        Universe::Renderer::BeginScene(m_Camera);
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
    Universe::Ref<Universe::Shader> m_Shader;
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
