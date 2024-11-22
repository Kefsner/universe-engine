#include "universe.hpp"

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
        // Create vertex buffer
        m_VertexBuffer = Universe::VertexBuffer::Create(vertices, sizeof(vertices));
        // Create vertex array
        m_VertexArray = Universe::VertexArray::Create();
        // Bind vertex buffer to vertex array
        std::shared_ptr<Universe::VertexBuffer> sharedVertexBuffer = std::move(m_VertexBuffer);
        m_VertexArray->AddVertexBuffer(sharedVertexBuffer);

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
        // Universe::Renderer::Submit();
        Universe::Renderer::EndScene();
    }

    void OnEvent(Universe::Event& event) override
    {
        UE_TRACE("{0}", event.ToString());
    }

private:
    std::unique_ptr<Universe::VertexBuffer> m_VertexBuffer;
    std::unique_ptr<Universe::VertexArray> m_VertexArray;
    std::unique_ptr<Universe::Shader> m_Shader;
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
