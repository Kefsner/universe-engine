#include "GameLayer.hpp"

#include <glm/glm.hpp>

namespace Universe
{   
    GameLayer::GameLayer()
    {
        std::shared_ptr<Texture> blockTextures = AssetManager::LoadTexture("assets/blocks.png");

        m_BlockTextureAtlas = std::make_shared<TextureAtlas>(blockTextures, 1, 4);
    }

    void GameLayer::RenderBlock(Block block, glm::vec3 position)
    {
        int blockID = static_cast<int>(block.GetType());
        VoxelRenderer3D::DrawCube(position, m_BlockTextureAtlas, blockID);
    }

    void GameLayer::OnUpdate()
    {
        Block GRASS_BLOCK = Block(BlockType::GRASS);
        glm::vec3 position = {-1.0f, 0.0f, 0.0f};
        RenderBlock(GRASS_BLOCK, position);

        Block GRASS_SIDE = Block(BlockType::GRASS_SIDE);
        glm::vec3 position2 = {0.0f, 0.0f, 0.0f};
        RenderBlock(GRASS_SIDE, position2);

        Block DIRT_BLOCK = Block(BlockType::DIRT);
        glm::vec3 position3 = {1.0f, 0.0f, 0.0f};
        RenderBlock(DIRT_BLOCK, position3);
    };
}