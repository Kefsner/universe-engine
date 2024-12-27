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
            layout(location = 3) in float a_TexIndex;
            layout(location = 4) in float a_TilingFactor;

            out vec4 v_Color;
            out vec2 v_TexCoord;
            out float v_TexIndex;
            out float v_TilingFactor;

            void main()
            {
                v_Color = a_Color;
                v_TexCoord = a_TexCoord;
                v_TexIndex = a_TexIndex;
                v_TilingFactor = a_TilingFactor;
                gl_Position = a_Position;
            }
        )";

        static const char* fragmentShaderSource = R"(
            #version 330 core

            in vec4 v_Color;
            in vec2 v_TexCoord;
            in float v_TexIndex;
            in float v_TilingFactor;

            uniform sampler2D u_Textures[32];

            out vec4 color;

            void main()
            {
                int index = int(v_TexIndex);
                color = texture(u_Textures[index], v_TexCoord * v_TilingFactor) * v_Color;
            }
        )";
        
        struct QuadVertex
        {
            glm::vec3 position;
            glm::vec4 color;
            glm::vec2 texCoord;
            float texIndex;
            float tilingFactor;
        };

        struct renderer2DData
        {
            Ref<VertexArray> vertexArray;
            Ref<VertexBuffer> vertexBuffer;
            uint32_t indexBufferCount;
            Ref<Shader> shader;
            Ref<Texture2D> whiteTexture;

            glm::vec4 quadVertexPositions[4];

            std::array<Ref<Texture2D>, 32> textureSlots;
            uint32_t textureSlotIndex = 1;

            QuadVertex* vertexBufferBase = nullptr; // Pre-allocated array for vertex data
            QuadVertex* vertexBufferPtr = nullptr;  // Pointer to append vertex data
            uint32_t quadIndexCount = 0;            // Number of indices for the current batch
        };
        
        static renderer2DData s_Data;

        void Renderer2D::Init()
        {
            // Allocate memory for the CPU-side vertex buffer
            s_Data.vertexBufferBase = new QuadVertex[4];
            s_Data.vertexBufferPtr = s_Data.vertexBufferBase; // Set the pointer to the start of the buffer

            // Initialize GPU-side buffers
            s_Data.vertexArray = VertexArray::Create();
            s_Data.vertexBuffer = VertexBuffer::Create(sizeof(QuadVertex) * 4);
            s_Data.vertexBuffer->SetLayout({
                { ShaderDataType::Float3, "a_Position"     },
                { ShaderDataType::Float4, "a_Color"        },
                { ShaderDataType::Float2, "a_TexCoord"     },
                { ShaderDataType::Float,  "a_TexIndex"     },
                { ShaderDataType::Float,  "a_TilingFactor" }
            });
            s_Data.vertexArray->AddVertexBuffer(s_Data.vertexBuffer);

            uint32_t numberOfIndices = 6;
            std::vector<uint32_t> indices(numberOfIndices);
            uint32_t offset = 0;
            for (uint32_t i = 0; i < numberOfIndices; i += 6)
            {
                indices[i + 0] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;

                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;

                offset += 4;
            }

            s_Data.indexBufferCount = static_cast<uint32_t>(indices.size());
            Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), s_Data.indexBufferCount);
            s_Data.vertexArray->SetIndexBuffer(indexBuffer);
            
            s_Data.shader = Shader::Create("Renderer2D", vertexShaderSource, fragmentShaderSource);

            uint32_t whiteTextureData = 0xffffffff;
            s_Data.whiteTexture = Texture2D::Create(TextureSpecification());
            s_Data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
            s_Data.textureSlots[0] = s_Data.whiteTexture;

            int32_t samplers[32];
            for (int32_t i = 0; i < 32; i++)
                samplers[i] = i;

            s_Data.shader->Bind();
            s_Data.shader->SetUniformIntArray("u_Textures", samplers, 32);

            // Start generating vertex data
            s_Data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
            s_Data.quadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
            s_Data.quadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
            s_Data.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
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

            s_Data.vertexBufferPtr = s_Data.vertexBufferBase;
        }

        void Renderer2D::EndScene()
        {
            uint32_t dataSize = static_cast<uint32_t>((uint8_t*)s_Data.vertexBufferPtr - (uint8_t*)s_Data.vertexBufferBase);
            s_Data.vertexBuffer->SetData(s_Data.vertexBufferBase, dataSize);

            s_Data.vertexArray->Bind();
            
            for (uint32_t i = 0; i < s_Data.textureSlotIndex; i++)
                s_Data.textureSlots[i]->Bind(i);

            RenderCommand::DrawIndexed(s_Data.indexBufferCount);
        }

        void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
        {
            DrawQuad({ position.x, position.y, 0.0f }, size, color);
        }

        void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

            constexpr uint32_t quadVertexCount = 4;
            constexpr uint32_t textureIndex = 0; // White texture
            constexpr glm::vec2 texCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

            for (uint32_t i = 0; i < quadVertexCount; i++)
            {
                s_Data.vertexBufferPtr->position = transform * s_Data.quadVertexPositions[i];
                s_Data.vertexBufferPtr->color = color;
                s_Data.vertexBufferPtr->texCoord = texCoords[i];
                s_Data.vertexBufferPtr->texIndex = textureIndex;
                s_Data.vertexBufferPtr->tilingFactor = 1.0f;
                s_Data.vertexBufferPtr++;
            }
        }

        void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture)
        {
            DrawQuad({ position.x, position.y, 0.0f }, size, color, texture);
        }

        void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture)
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

            constexpr uint32_t quadVertexCount = 4;
            constexpr glm::vec2 texCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

            float textureIndex = 0.0f;

            for (uint32_t i = 1; i < s_Data.textureSlotIndex; i++)
            {
                if (s_Data.textureSlots[i] == texture)
                {
                    textureIndex = static_cast<float>(i);
                    break;
                }
            }

            if (textureIndex == 0.0f)
            {
                textureIndex = static_cast<float>(s_Data.textureSlotIndex);
                s_Data.textureSlots[s_Data.textureSlotIndex] = texture;
                s_Data.textureSlotIndex++;
            }

            for (uint32_t i = 0; i < quadVertexCount; i++)
            {
                s_Data.vertexBufferPtr->position = transform * s_Data.quadVertexPositions[i];
                s_Data.vertexBufferPtr->color = color;
                s_Data.vertexBufferPtr->texCoord = texCoords[i];
                s_Data.vertexBufferPtr->texIndex = textureIndex;
                s_Data.vertexBufferPtr->tilingFactor = 1.0f;
                s_Data.vertexBufferPtr++;
            }
        }
    }