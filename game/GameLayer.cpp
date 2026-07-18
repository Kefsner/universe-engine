#include "GameLayer.hpp"

#include <glm/glm.hpp>

namespace Universe
{   
    GameLayer::GameLayer()
    {
        std::shared_ptr<Texture> blockTextures = AssetManager::LoadTexture("assets/blocks.png");

        m_BlockTextureAtlas = std::make_unique<TextureAtlas>(blockTextures, 1, 4);
    }

    void GameLayer::RenderBlock(Block block, glm::vec3 position)
    {
        int blockID = static_cast<int>(block.GetType());
        glm::vec2 texCoord = m_BlockTextureAtlas->GetTexCoordFromID(blockID);   
        VoxelRenderer3D::DrawCube(position, m_BlockTextureAtlas->GetTexture(), texCoord);
    }

    void GameLayer::OnUpdate()
    {
        Block GRASS_BLOCK = Block(BlockType::GRASS);
        glm::vec3 position = {0.0f, 0.0f, 0.0f};
        RenderBlock(GRASS_BLOCK, position);
    };
}