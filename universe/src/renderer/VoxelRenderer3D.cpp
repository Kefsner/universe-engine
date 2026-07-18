#include "core/Logger.hpp"

#include "renderer/VoxelRenderer3D.hpp"

#include "renderer/VertexArray.hpp"
#include "renderer/VertexBuffer.hpp"
#include "renderer/IndexBuffer.hpp"

#include "renderer/Shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace Universe
{
    struct VoxelRenderer3DData
    {
        std::unique_ptr<VertexBuffer> s_VertexBuffer;
        std::unique_ptr<VertexArray> s_VertexArray;
        std::unique_ptr<IndexBuffer> s_IndexBuffer;

        // Cubes
        float s_CubeVertices[24] = {
            // Front
            -0.5f, -0.5f,  0.5f, // Bottom left
             0.5f, -0.5f,  0.5f, // Bottom right
             0.5f,  0.5f,  0.5f, // Top right
            -0.5f,  0.5f,  0.5f, // Top left

            // Back
            -0.5f, -0.5f, -0.5f, // Bottom left
             0.5f, -0.5f, -0.5f, // Bottom right
             0.5f,  0.5f, -0.5f, // Top right
            -0.5f,  0.5f, -0.5f, // Top left
        };

        unsigned int s_CubeIndices[36] = {
            // Face 1 - Front
            0, 1, 2,
            0, 2, 3,
            // Face 2 - Right
            1, 5, 6,
            1, 6, 2,
            // Face 3 - Back
            5, 4, 7,
            5, 7, 6,
            // Face 4 - Left
            4, 0, 3,
            4, 3, 7,
            // Face 5 - Bottom
            0, 4, 5,
            0, 5, 1,
            // Face 6 - Top
            3, 2, 6,
            3, 6, 7
        };

        std::unique_ptr<Shader> s_Shaders ;
    };

    static std::unique_ptr<VoxelRenderer3DData> s_Data;
    
    void VoxelRenderer3D::Init()
    {
        s_Data = std::make_unique<VoxelRenderer3DData>();

        s_Data->s_VertexBuffer = std::make_unique<VertexBuffer>();
        UE_CORE_INFO("Testando2");
        s_Data->s_VertexBuffer->SetData(s_Data->s_CubeVertices, 24);
        UE_CORE_INFO("Testando2");
        s_Data->s_IndexBuffer = std::make_unique<IndexBuffer>();
        s_Data->s_IndexBuffer->SetData(s_Data->s_CubeIndices, 36);

        s_Data->s_VertexArray = std::make_unique<VertexArray>();
        s_Data->s_VertexArray->AttachBuffers(*s_Data->s_VertexBuffer, *s_Data->s_IndexBuffer);
        s_Data->s_VertexArray->SetAttributes();

        s_Data->s_Shaders = std::make_unique<Shader>();
        s_Data->s_Shaders->Bind();

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3({0.0f, 0.0f, -3.0f}));
        s_Data->s_Shaders->SetMat4Uniform(view, "u_View");

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
        s_Data->s_Shaders->SetMat4Uniform(projection, "u_Projection");
    }

    void VoxelRenderer3D::DrawCube(glm::vec3 position, std::shared_ptr<Texture> texture, glm::vec2 texCoord)
    {
        s_Data->s_VertexArray->Bind();
        s_Data->s_Shaders->Bind();

        // s_Data->s_Shaders->SetVec2Uniform(texCoord, "u_TexCoord")
        texture->Bind(s_Data->s_Shaders->GetProgram());

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::rotate(transform, glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        s_Data->s_Shaders->SetMat4Uniform(transform, "u_Transform");

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}