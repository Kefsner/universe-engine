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
    }

    void GameLayer::RenderBlock(Block block, glm::vec3 position)
    {
        int blockID = static_cast<int>(block.GetType());
        VoxelRenderer3D::DrawCube(position, m_BlockTextureAtlas, blockID);
    }

    void GameLayer::OnUpdate()
    {
        VoxelRenderer3D::BeginScene(*m_Camera);

        glm::vec3 cameraPosition = m_Camera->GetPosition();
        float cameraSpeed = 0.04f;

        if (Input::IsKeyPressed(Key::W))
            cameraPosition += glm::vec3(0.0f, 0.0f, -cameraSpeed);
        if (Input::IsKeyPressed(Key::S))
            cameraPosition += glm::vec3(0.0f, 0.0f, cameraSpeed);
        if (Input::IsKeyPressed(Key::A))
            cameraPosition += glm::vec3(-cameraSpeed, 0.0f, 0.0f);
        if (Input::IsKeyPressed(Key::D))
            cameraPosition += glm::vec3(cameraSpeed, 0.0f, 0.0f);

        if (Input::IsKeyPressed(Key::Space))
            cameraPosition += glm::vec3(0.0f, cameraSpeed, 0.0f);
        if (Input::IsKeyPressed(Key::LeftShift))
            cameraPosition += glm::vec3(0.0f, -cameraSpeed, 0.0f);

        m_Camera->SetPosition(cameraPosition);

        Block GRASS_SIDE = Block(BlockType::GRASS_SIDE);
        glm::vec3 position2 = {1.0f, 0.0f, 0.0f};
        RenderBlock(GRASS_SIDE, position2);

        Input::IsKeyPressed(Key::D1);
    };
}