#include "GameLayer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Universe
{   
    GameLayer::GameLayer()
    {
        std::shared_ptr<Texture> blockTextures = AssetManager::LoadTexture("assets/blocks.png");

        m_BlockTextureAtlas = std::make_shared<TextureAtlas>(blockTextures, 1, 4);
        m_Camera = std::make_unique<Camera>(glm::vec3({0.0f, 0.0f, 3.0f}));
        m_CursorDisabled = true;
        Input::DisableCursor(m_CursorDisabled);
    }

    void GameLayer::RenderBlock(Block block, glm::vec3 position)
    {
        int blockID = static_cast<int>(block.GetType());
        VoxelRenderer3D::DrawCube(position, m_BlockTextureAtlas, blockID);
    }

    void GameLayer::OnUpdate(Timestep ts)
    {
        VoxelRenderer3D::BeginScene(*m_Camera);

        if (Input::IsKeyPressed(Key::Escape))
        {
            m_CursorDisabled = !m_CursorDisabled;
            Input::DisableCursor(m_CursorDisabled);
        }

        glm::vec3 plane;

        glm::vec3 cameraPosition = m_Camera->GetPosition();
        float cameraSpeed = 8.3f;
        float cameraAngleSpeed = 0.05f;

        if (Input::IsKeyPressed(Key::W))
            cameraPosition += ts * cameraSpeed * m_Camera->GetCameraFront();
        if (Input::IsKeyPressed(Key::S))
            cameraPosition -= ts * cameraSpeed * m_Camera->GetCameraFront();
        if (Input::IsKeyPressed(Key::A))
        {
            plane = m_Camera->GetCameraFront();
            cameraPosition -= glm::normalize(
                glm::cross(glm::vec3({plane.x, 0.0f, plane.z}), glm::vec3({0.0f, 1.0f, 0.0f}))
            ) * (cameraSpeed * ts);
        }
        if (Input::IsKeyPressed(Key::D))
        {
            plane = m_Camera->GetCameraFront();
            cameraPosition += glm::normalize(
                glm::cross(glm::vec3({plane.x, 0.0f, plane.z}), glm::vec3({0.0f, 1.0f, 0.0f}))
            ) * (cameraSpeed * ts);
        }

        if (Input::IsKeyPressed(Key::Space))
            cameraPosition += glm::vec3(0.0f, cameraSpeed * ts, 0.0f);
        if (Input::IsKeyPressed(Key::LeftShift))
            cameraPosition += glm::vec3(0.0f, -cameraSpeed * ts, 0.0f);

        m_Camera->SetPosition(cameraPosition);

        glm::vec2 mousePos = Input::GetMousePos();
    
        float xOffset = m_LastMouseXPos - mousePos.x;
        float yOffset = m_LastMouseYPos - mousePos.y;

        m_Yaw -= xOffset * cameraAngleSpeed;
        m_Pitch += yOffset * cameraAngleSpeed;

        m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

        m_LastMouseXPos = mousePos.x;
        m_LastMouseYPos = mousePos.y;

        m_Camera->SetOrientation(m_Yaw, m_Pitch);

        glm::vec3 blockPosition;
        for (int j = -50; j < 50; j++)
        {
            for (int i = -50; i < 50; i++)
            {
                blockPosition = {i, 0.0f, j};
                RenderBlock(Block(BlockType::GRASS), blockPosition);
            }
        }
    };
}