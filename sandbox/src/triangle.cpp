#include "triangle.hpp"

void Triangle::OnAttach()
{
    float vertices[] = {
        // Positions    // Colors
        -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-left
         0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // Bottom-right
         0.0f,  0.5f,   0.0f, 0.0f, 1.0f  // Top
    };

    // Create a buffer
    Universe::Ref<Universe::VertexBuffer> vertexBuffer;
    vertexBuffer = Universe::VertexBuffer::Create(vertices, sizeof(vertices));
    vertexBuffer->SetLayout({
        { Universe::ShaderDataType::Float2, "a_Position" },
        { Universe::ShaderDataType::Float3, "a_Color" }
    });

    // Create a vertex array
    m_VertexArray = Universe::VertexArray::Create();

    m_VertexArray->AddVertexBuffer(vertexBuffer);

    // Shader
    const char* vertexShaderSource = R"(
        #version 460 core

        layout(location = 0) in vec2 a_Position;
        layout(location = 1) in vec3 a_Color;

        out vec4 v_Color;

        void main()
        {
            gl_Position = vec4(a_Position, 0.0, 1.0);
            v_Color = vec4(a_Color, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 460 core

        in vec4 v_Color;

        out vec4 color;

        void main()
        {
            color = vec4(v_Color);
        }
    )";

    Universe::Ref<Universe::Shader> shader;
    shader = Universe::Shader::Create("Triangle", vertexShaderSource, fragmentShaderSource);
    shader->Bind();
}

void Triangle::OnDetach()
{
}

void Triangle::OnUpdate(Universe::Timestep ts)
{
    Universe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Universe::RenderCommand::Clear();
    m_VertexArray->Bind();
    Universe::RenderCommand::DrawArrays(0, 3);
}

void Triangle::OnEvent(Universe::Event& event)
{
    UE_CORE_TRACE("{0}", event.ToString());
}