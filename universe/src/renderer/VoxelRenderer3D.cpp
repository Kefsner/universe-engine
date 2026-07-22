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
        float s_CubeVertices[192] = {
            // x,y,z,r,g,b,u,v
            // Front
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Bottom left
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Bottom right
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Top right
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Top left

            // Left
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,     

            // Back
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

            // Right
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

            // Top
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

            // Down
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };

        unsigned int s_CubeIndices[36] = {
            // Face 1 - Front
            0, 1, 2,
            0, 2, 3,
            // Face 2 - Left
            4, 5, 6,
            4, 6, 7,
            // Face 3 - Back
            8,  9, 10,
            8, 10, 11,
            // Face 4 - Right
            12, 13, 14,
            12, 14, 15,
            // Face 5 - Top
            16, 17, 18,
            16, 18, 19,
            // Face 6 - Down
            20, 21, 22,
            20, 22, 23
        };

        std::unique_ptr<Shader> s_Shaders ;
    };

    static std::unique_ptr<VoxelRenderer3DData> s_Data;
    
    void VoxelRenderer3D::Init()
    {
        s_Data = std::make_unique<VoxelRenderer3DData>();

        s_Data->s_VertexBuffer = std::make_unique<VertexBuffer>();
        s_Data->s_VertexBuffer->SetData(s_Data->s_CubeVertices, 192);
        s_Data->s_IndexBuffer = std::make_unique<IndexBuffer>();
        s_Data->s_IndexBuffer->SetData(s_Data->s_CubeIndices, 36);

        s_Data->s_VertexArray = std::make_unique<VertexArray>();
        s_Data->s_VertexArray->AttachBuffers(*s_Data->s_VertexBuffer, *s_Data->s_IndexBuffer);
        s_Data->s_VertexArray->SetAttributes();

        s_Data->s_Shaders = std::make_unique<Shader>();
    }

    void VoxelRenderer3D::BeginScene(Camera& camera)
    {
        s_Data->s_Shaders->Bind();
        s_Data->s_Shaders->SetMat4Uniform(camera.GetProjectionViewMatrix(), "u_ProjectionView");
    }

    void VoxelRenderer3D::DrawCube(glm::vec3 position, std::shared_ptr<TextureAtlas> atlas, int cellID)
    {
        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        view = glm::lookAt(glm::vec3(camX, 1.0f, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); 
        s_Data->s_Shaders->SetMat4Uniform(view, "u_View");

        s_Data->s_VertexArray->Bind();
        s_Data->s_Shaders->Bind();
        atlas->GetTexture()->Bind(s_Data->s_Shaders->GetProgram());

        float cellWidth = atlas->GetTexture()->GetWidth() / atlas->GetColumns();
        float cellHeight = atlas->GetTexture()->GetHeight() / atlas->GetRows();
        float normalizedCellWidth = cellWidth / atlas->GetTexture()->GetWidth();
        float normalizedCellHeight = cellHeight / atlas->GetTexture()->GetHeight();
        glm::vec2 normalizedCellSize = glm::vec2({normalizedCellWidth, normalizedCellHeight});
        s_Data->s_Shaders->SetVec2Uniform(normalizedCellSize, "u_CellSize");

        int row = cellID / atlas->GetColumns();
        int column = cellID % atlas->GetColumns();
        float uOffset = column * cellWidth;
        float vOffset = row * cellHeight;
        float normalizedUOffset = uOffset / atlas->GetTexture()->GetWidth();
        float normalizedVOffset = vOffset / atlas->GetTexture()->GetHeight();
        glm::vec2 normalizedUVOffset = glm::vec2({normalizedUOffset, normalizedVOffset});
        s_Data->s_Shaders->SetVec2Uniform(normalizedUVOffset, "u_CellOffset");

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        s_Data->s_Shaders->SetMat4Uniform(transform, "u_Transform");

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}