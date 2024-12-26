#include "pch.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "universe/renderer/renderer2D.hpp"
#include "universe/renderer/render_command.hpp"
#include "universe/renderer/vertex_array.hpp"

namespace Universe
{    
    struct renderer2DData
    {
        Ref<VertexArray> vertexArray;
        Ref<Shader> shader;
        uint32_t indexBufferCount;
    };
    
    static renderer2DData s_Data;

    void Renderer2D::Init()
    {
        float vertices[] = {
            // Positions
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
        };
        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };

        s_Data.vertexArray = VertexArray::Create();
        {
        Ref<VertexBuffer> vertexBuffer;
        vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        vertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position"     },
            // { ShaderDataType::Float4, "a_Color"        },
            // { ShaderDataType::Float2, "a_TexCoord"     },
            // { ShaderDataType::Float,  "a_TexIndex"     },
            // { ShaderDataType::Float,  "a_TilingFactor" }
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

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_Transform;

            void main()
            {
                gl_Position = u_Transform * vec4(a_Position, 1.0);
            }
        )";

        const char* fragmentShaderSource = R"(
            #version 460 core

            uniform vec4 u_Color;

            out vec4 color;

            void main()
            {
                color = u_Color;
            }
        )";
        s_Data.shader = Shader::Create("Renderer2D", vertexShaderSource, fragmentShaderSource);
        s_Data.shader->Bind();
        s_Data.vertexArray->Bind();
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
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad()
    {
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        s_Data.shader->Bind();
        s_Data.shader->SetUniformMat4("u_Transform", transform);
        s_Data.shader->SetUniformFloat4("u_Color", color);

        RenderCommand::DrawIndexed(s_Data.indexBufferCount);
    }
}