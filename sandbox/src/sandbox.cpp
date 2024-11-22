#include "universe.hpp"

class ExampleLayer : public Universe::Layer
{
public:
    ExampleLayer()
    {
        // Vertex data for a triangle
        float vertices[] = {
             0.0f,  0.5f, 0.0f, // Top
            -0.5f, -0.5f, 0.0f, // Bottom left
             0.5f, -0.5f, 0.0f  // Bottom right
        };
        m_VertexBuffer = Universe::VertexBuffer::Create(vertices, sizeof(vertices));
        {
            Universe::BufferLayout layout = {
                { Universe::ShaderDataType::Float3, "a_Position" },
                { Universe::ShaderDataType::Float4, "a_Color" }
            };
            m_VertexBuffer->SetLayout(layout);
        }
        uint32_t indices[] = { 0, 1, 2 };
        m_IndexBuffer = Universe::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        m_VertexArray = Universe::VertexArray::Create();
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        // Shader source code
        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;

            void main()
            {
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color
            }
        )";

        // Shader
        m_Shader = Universe::Shader::Create(vertexSrc, fragmentSrc);
    }

    void OnUpdate() override
    {
        Universe::Renderer::BeginScene();
        Universe::Renderer::Submit(m_Shader, m_VertexArray);
        Universe::Renderer::EndScene();
    }

    void OnEvent(Universe::Event& event) override
    {
        UE_TRACE("{0}", event.ToString());
    }

private:
    Universe::Ref<Universe::VertexBuffer> m_VertexBuffer;
    Universe::Ref<Universe::IndexBuffer> m_IndexBuffer;
    Universe::Ref<Universe::VertexArray> m_VertexArray;
    Universe::Ref<Universe::Shader> m_Shader;

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
