#include "pch.hpp"

#include "universe/renderer/renderer2D.hpp"
#include "universe/renderer/render_command.hpp"
#include "universe/renderer/shader.hpp"
#include "universe/renderer/vertex_array.hpp"

// TODO: Remove this
#include "universe/renderer/opengl/opengl_shader.hpp"

namespace Universe {

    struct renderer2DData
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> QuadShader;
    };

    static renderer2DData* s_Data;

    void Renderer2D::Init()
    {
        s_Data = new renderer2DData();
        // Vertices
        float vertices[4*2] = {
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f,
            -0.5f, -0.5f
        };

        // Vertex Buffer
        Ref<VertexBuffer> VertexBuffer;
        VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        BufferLayout layout = {
            { ShaderDataType::Float2, "a_Position" }
        };
        VertexBuffer->SetLayout(layout);

        // Index Buffer
        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> IndexBuffer;
        IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        // Vertex Array
        s_Data->QuadVertexArray = VertexArray::Create();
        s_Data->QuadVertexArray->AddVertexBuffer(VertexBuffer);
        s_Data->QuadVertexArray->SetIndexBuffer(IndexBuffer);

        // Shader
        s_Data->QuadShader = Shader::Create("../../sandbox/assets/shaders/square.glsl");
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
        s_Data->QuadShader->Bind(); // For safety since it is already called in BeginScene. We could add a check to see if it is already bound to reduce overhead
        s_Data->QuadShader->SetFloat4("u_Color", color);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->QuadShader->SetMat4("u_Transform", transform);
        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
}