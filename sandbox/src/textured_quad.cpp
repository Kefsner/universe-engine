#include <glad/glad.h>
#include <stb_image.h>

#include "textured_quad.hpp"

void TexturedQuad::OnAttach()
{
    float vertices[] = {
        // Positions  // TexCoords
        -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
         0.5f, -0.5f, 1.0f, 0.0f, // Bottom-right
         0.5f,  0.5f, 1.0f, 1.0f, // Top-right
        -0.5f,  0.5f, 0.0f, 1.0f  // Top-left
    };
    uint32_t indices[] = {
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
    };

    // Create a vertex array
    m_VertexArray = Universe::VertexArray::Create();

    // Create a buffer
    Universe::Ref<Universe::VertexBuffer> vertexBuffer;
    vertexBuffer = Universe::VertexBuffer::Create(vertices, sizeof(vertices));
    vertexBuffer->SetLayout({
        { Universe::ShaderDataType::Float2, "a_Position" },
        { Universe::ShaderDataType::Float2, "a_TexCoord" }
    });

    // Add the buffer to the vertex array
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    // Create an index buffer
    m_IndexBufferCount = sizeof(indices) / sizeof(uint32_t);
    Universe::Ref<Universe::IndexBuffer> indexBuffer;
    indexBuffer = Universe::IndexBuffer::Create(indices, m_IndexBufferCount);

    // Add the index buffer to the vertex array
    m_VertexArray->SetIndexBuffer(indexBuffer);

    // Shader
    const char* vertexShaderSource = R"(
        #version 460 core

        layout(location = 0) in vec2 a_Position;
        layout(location = 1) in vec2 a_TexCoord;

        out vec2 v_TexCoord;

        void main()
        {
            gl_Position = vec4(a_Position, 0.0, 1.0);
            v_TexCoord = a_TexCoord;
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 460 core

        in vec2 v_TexCoord;

        out vec4 color;

        uniform sampler2D u_Texture;

        void main()
        {
            color = texture(u_Texture, v_TexCoord);
        }
    )";

    m_Shader = Universe::Shader::Create("TexturedQuad", vertexShaderSource, fragmentShaderSource);
    m_Shader->Bind();
    m_Shader->SetUniformInt("u_Texture", 0);

    // Texture
    Universe::Ref<Universe::Texture2D> texture;
    m_Texture = Universe::Texture2D::Create("sandbox/assets/textures/checkerboard.png");
    uint32_t slot = 0;
    m_Texture->Bind(slot); // Needs the shader to be bound

    Universe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
}

void TexturedQuad::OnDetach()
{
}

void TexturedQuad::OnUpdate(Universe::Timestep ts)
{
    Universe::RenderCommand::Clear();
    m_VertexArray->Bind();
    Universe::RenderCommand::DrawIndexed(m_IndexBufferCount);
}

void TexturedQuad::OnEvent(Universe::Event& event)
{
    UE_CORE_TRACE("{0}", event.ToString());
}

