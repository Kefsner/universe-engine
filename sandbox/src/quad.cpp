#include "quad.hpp"

#include <glad/glad.h>

void Quad::OnAttach()
{
    float vertices[] = {
        // Position     // Color
        -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
         0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f, // Bottom-right
         0.5f,  0.5f,   0.0f, 0.0f, 1.0f, 1.0f, // Top-right
        -0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 0.3f  // Top-left
    };

    // Create a buffer
    Universe::Ref<Universe::VertexBuffer> vertexBuffer;
    vertexBuffer = Universe::VertexBuffer::Create(vertices, sizeof(vertices));
    vertexBuffer->SetLayout({
        { Universe::ShaderDataType::Float2, "a_Position" },
        { Universe::ShaderDataType::Float4, "a_Color" }
    });

    // Create a vertex array
    m_VertexArray = Universe::VertexArray::Create();

    // Add the buffer to the vertex array
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    // Create an index buffer
    uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
    m_IndexBufferCount = sizeof(indices) / sizeof(uint32_t);
    Universe::Ref<Universe::IndexBuffer> indexBuffer;
    indexBuffer = Universe::IndexBuffer::Create(indices, m_IndexBufferCount);

    // Add the index buffer to the vertex array
    m_VertexArray->SetIndexBuffer(indexBuffer);

    // Shader
    const char* vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec2 a_Position;
        layout(location = 1) in vec4 a_Color;

        out vec4 v_Color;

        void main()
        {
            gl_Position = vec4(a_Position, 0.0, 1.0);
            v_Color = a_Color;
        }
    )";

    const char* fragmentSrc = R"(
        #version 330 core

        in vec4 v_Color;

        out vec4 color;

        void main()
        {
            color = v_Color;
        }
    )";

    Universe::Ref<Universe::Shader> shader;
    shader = Universe::Shader::Create("Quad", vertexSrc, fragmentSrc);
    shader->Bind();
}

void Quad::OnDetach()
{
}

void Quad::OnUpdate(Universe::Timestep ts)
{
    Universe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Universe::RenderCommand::Clear();
    m_VertexArray->Bind();
    Universe::RenderCommand::DrawIndexed(m_IndexBufferCount);
}

void Quad::OnEvent(Universe::Event& event)
{
    UE_CORE_TRACE("{0}", event.ToString());
}