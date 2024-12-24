#include "pch.hpp"

#include "universe/renderer/renderer2D.hpp"
#include "universe/renderer/render_command.hpp"
#include "universe/renderer/vertex_array.hpp"

namespace Universe
{
    struct renderer2DData
    {
        Ref<VertexArray> vertexArray;
        uint32_t indexBufferCount;
    };
    
    static renderer2DData s_Data;

    void Renderer2D::Init()
    {
        float vertices[] = {
            // Positions    // Colors
            -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-left
             0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // Bottom-right
             0.5f,  0.5f,   0.0f, 0.0f, 1.0f, // Top-right
            -0.5f,  0.5f,   1.0f, 1.0f, 0.0f  // Top-left
        };
        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };

        s_Data.vertexArray = VertexArray::Create();
        {
        Ref<VertexBuffer> vertexBuffer;
        vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        vertexBuffer->SetLayout({
            { ShaderDataType::Float2, "a_Position" },
            { ShaderDataType::Float3, "a_Color" }
        });
        s_Data.vertexArray->AddVertexBuffer(vertexBuffer);
        }
        s_Data.indexBufferCount = sizeof(indices) / sizeof(uint32_t);
        {
        Ref<IndexBuffer> indexBuffer;
        indexBuffer = IndexBuffer::Create(indices, s_Data.indexBufferCount);
        s_Data.vertexArray->SetIndexBuffer(indexBuffer);
        }
        {
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
        Ref<Shader> shader;
        shader = Shader::Create("Renderer2D", vertexShaderSource, fragmentShaderSource);
        shader->Bind();
        }
    }

    void Renderer2D::Shutdown()
    {
    }

    void Renderer2D::SetClearColor(const glm::vec4& color)
    {
        RenderCommand::SetClearColor(color);
    }

    void Renderer2D::BeginScene()
    {
        RenderCommand::Clear();
        s_Data.vertexArray->Bind();
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad()
    {
        RenderCommand::DrawIndexed(s_Data.indexBufferCount);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad();
    }
}