#include "pch.hpp"

#include "universe/renderer/renderer2D.hpp"
#include "universe/renderer/render_command.hpp"
#include "universe/renderer/shader.hpp"
#include "universe/renderer/vertex_array.hpp"

namespace Universe {

    struct renderer2DData
    {
        Ref<VertexArray> QuadVA;
        Ref<Shader> QuadShader;
        Ref<Texture2D> WhiteTexture;
    };

    static renderer2DData* s_Data;

    void Renderer2D::Init()
    {
        s_Data = new renderer2DData();
        // Vertices
        float vertices[4 * 5] = {
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f
        };

        // Vertex Buffer
        Ref<VertexBuffer> VertexBuffer;
        VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" }
        };
        VertexBuffer->SetLayout(layout);

        // Index Buffer
        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> IndexBuffer;
        IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        // Vertex Array
        s_Data->QuadVA = VertexArray::Create();
        s_Data->QuadVA->AddVertexBuffer(VertexBuffer);
        s_Data->QuadVA->SetIndexBuffer(IndexBuffer);

        // White Texture
        s_Data->WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        // Shader
        s_Data->QuadShader = Shader::Create("../../sandbox/assets/shaders/texture.glsl");
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(OrthographicCamera& camera)
    {
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        RenderCommand::Clear();
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        s_Data->QuadShader->SetFloat4("u_Color", color);
        s_Data->WhiteTexture->Bind();
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->QuadShader->SetMat4("u_Transform", transform);
        s_Data->QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVA);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        s_Data->QuadShader->SetFloat4("u_Color", glm::vec4(1.0f));
        texture->Bind();
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->QuadShader->SetMat4("u_Transform", transform);
        s_Data->QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVA);
    }
}