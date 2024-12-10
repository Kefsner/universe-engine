#include "pch.hpp"

#include "universe/renderer/renderer2D.hpp"
#include "universe/renderer/render_command.hpp"
#include "universe/renderer/shader.hpp"
#include "universe/renderer/vertex_array.hpp"

namespace Universe {

    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
    };

    struct renderer2DData
    {
        const uint32_t MaxQuads = 10000;
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;
        const uint32_t MaxTextureSlots = 32;

        Ref<VertexArray> QuadVA;
        Ref<VertexBuffer> QuadVB;
        Ref<Shader> QuadShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;
    };

    static renderer2DData s_Data;


    void Renderer2D::Init()
    {
        // Vertex Buffer
        s_Data.QuadVB = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
        s_Data.QuadVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_TexCoord" }
        });
        s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

        // Index Buffer
        uint32_t* QuadIndices = new uint32_t[s_Data.MaxIndices];
        uint32_t offset = 0;
        for (uint32_t i = 0, offset = 0; i < s_Data.MaxIndices; i += 6, offset += 4)
        {
            QuadIndices[i + 0] = offset + 0;
            QuadIndices[i + 1] = offset + 1;
            QuadIndices[i + 2] = offset + 2;
            QuadIndices[i + 3] = offset + 2;
            QuadIndices[i + 4] = offset + 3;
            QuadIndices[i + 5] = offset + 0;
        }
        Ref<IndexBuffer> QuadIB;
        QuadIB = IndexBuffer::Create(QuadIndices, s_Data.MaxIndices);

        // Vertex Array
        s_Data.QuadVA = VertexArray::Create();
        s_Data.QuadVA->AddVertexBuffer(s_Data.QuadVB);
        s_Data.QuadVA->SetIndexBuffer(QuadIB);

        delete[] QuadIndices;

        // White Texture
        s_Data.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        // Shader
        s_Data.QuadShader = Shader::Create("../../sandbox/assets/shaders/texture.glsl");
        s_Data.QuadShader->Bind();
        s_Data.QuadShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown()
    {
    }

    void Renderer2D::BeginScene(OrthographicCamera& camera)
    {
        s_Data.QuadShader->Bind();
        s_Data.QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        RenderCommand::Clear();
    }

    void Renderer2D::EndScene()
    {
        uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
        s_Data.QuadVB->SetData(s_Data.QuadVertexBufferBase, dataSize);
        RenderCommand::DrawIndexed(s_Data.QuadVA, s_Data.QuadIndexCount);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        s_Data.QuadVertexBufferPtr->Position = { position.x, position.y, position.z };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor);
    }
    
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor)
    {
        s_Data.QuadShader->SetFloat4("u_Color", glm::vec4(1.0f));
        s_Data.QuadShader->SetFloat("u_TilingFactor", tilingFactor);
        texture->Bind();
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data.QuadShader->SetMat4("u_Transform", transform);
        s_Data.QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVA);
    }
}