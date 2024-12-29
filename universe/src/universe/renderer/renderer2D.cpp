#include "pch.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "universe/renderer/renderer2D.hpp"
#include "universe/renderer/render_command.hpp"
#include "universe/renderer/vertex_array.hpp"
#include "universe/renderer/texture.hpp"

namespace Universe
{
    // Temporary shaders
    static const char* vertexShaderSource = R"(
        #version 330 core

        layout(location = 0) in vec4 a_Position;
        layout(location = 1) in vec4 a_Color;
        layout(location = 2) in vec2 a_TexCoord;

        out vec4 v_Color;
        out vec2 v_TexCoord;

        uniform mat4 u_ViewProjection;

        void main()
        {
            v_Color = a_Color;
            v_TexCoord = a_TexCoord;
            gl_Position = u_ViewProjection * a_Position;
        }
    )";

    static const char* fragmentShaderSource = R"(
        #version 330 core

        in vec4 v_Color;
        in vec2 v_TexCoord;

        uniform sampler2D u_Textures;

        out vec4 color;

        void main()
        {
            color = texture(u_Textures, v_TexCoord) * v_Color;
        }
    )";
    
    struct QuadVertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texCoord;
    };

    struct renderer2DData
    {
        Ref<VertexArray> vertexArray;
        Ref<VertexBuffer> vertexBuffer;
        Ref<Shader> shader;
        Ref<Texture2D> whiteTexture;

        glm::vec4 quadVertexPositions[4];

        QuadVertex* vertexBufferBase = nullptr;
    };
    
    static renderer2DData s_Data;

    void Renderer2D::Init()
    {
        // Allocate CPU memory for the vertex buffer
        s_Data.vertexBufferBase = new QuadVertex[4];

        // Initialize GPU-side buffers
        s_Data.vertexArray = VertexArray::Create();
        s_Data.vertexBuffer = VertexBuffer::Create(sizeof(QuadVertex) * 4);
        s_Data.vertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position"     },
            { ShaderDataType::Float4, "a_Color"        },
            { ShaderDataType::Float2, "a_TexCoord"     },
        });
        s_Data.vertexArray->AddVertexBuffer(s_Data.vertexBuffer);

        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        s_Data.vertexArray->SetIndexBuffer(indexBuffer);
        
        // Create shader
        s_Data.shader = Shader::Create("Renderer2D", vertexShaderSource, fragmentShaderSource);

        // Set white texture
        uint32_t whiteTextureData = 0xffffffff;
        s_Data.whiteTexture = Texture2D::Create(TextureSpecification());
        s_Data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        // Set quad vertex positions (will be transformed by the model matrix)
        s_Data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.quadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.quadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
        s_Data.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    }

    void Renderer2D::Shutdown()
    {
        delete[] s_Data.vertexBufferBase;
    }

    void Renderer2D::SetClearColor(const glm::vec4& color)
    {
        RenderCommand::SetClearColor(color);
    }

    void Renderer2D::BeginScene(OrthographicCamera& camera)
    {
        s_Data.shader->Bind();
        s_Data.shader->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
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
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        constexpr glm::vec2 texCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

        for (uint32_t i = 0; i < 4; i++)
        {
            s_Data.vertexBufferBase[i].position = transform * s_Data.quadVertexPositions[i];
            s_Data.vertexBufferBase[i].color = color;
            s_Data.vertexBufferBase[i].texCoord = texCoords[i];
        }

        s_Data.whiteTexture->Bind(0);
        s_Data.vertexBuffer->SetData(s_Data.vertexBufferBase, sizeof(QuadVertex) * 4);
        s_Data.shader->Bind();
        s_Data.vertexArray->Bind();
        RenderCommand::DrawIndexed(6);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        constexpr glm::vec2 texCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

        for (uint32_t i = 0; i < 4; i++)
        {
            s_Data.vertexBufferBase[i].position = transform * s_Data.quadVertexPositions[i];
            s_Data.vertexBufferBase[i].color = color;
            s_Data.vertexBufferBase[i].texCoord = texCoords[i];
        }

        texture->Bind(0);
        s_Data.vertexBuffer->SetData(s_Data.vertexBufferBase, sizeof(QuadVertex) * 4);
        s_Data.shader->Bind();
        s_Data.vertexArray->Bind();
        RenderCommand::DrawIndexed(6);
    }
}