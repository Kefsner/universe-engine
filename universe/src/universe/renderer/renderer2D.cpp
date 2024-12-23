#include "pch.hpp"

#include "universe/renderer/renderer2D.hpp"
#include "universe/renderer/render_command.hpp"
#include "universe/renderer/vertex_array.hpp"

namespace Universe
{
    struct renderer2DData
    {
        Ref<VertexArray> vertexArray;
        uint32_t indexBufferCount = 0;
    };
    
    static renderer2DData s_Data;

    void Renderer2D::Init()
    {
        float vertices[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
        };
        uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };

        s_Data.vertexArray = VertexArray::Create();
        {
        Ref<VertexBuffer> vertexBuffer;
        vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        s_Data.vertexArray->AddVertexBuffer(vertexBuffer);
        }
        s_Data.indexBufferCount = sizeof(indices) / sizeof(uint32_t);
        {
        Ref<IndexBuffer> indexBuffer;
        indexBuffer = IndexBuffer::Create(indices, s_Data.indexBufferCount);
        s_Data.vertexArray->SetIndexBuffer(indexBuffer);
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