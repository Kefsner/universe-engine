#include "Game.hpp"

namespace Universe
{
    Game::Game()
    {
        UE_LOGGER("Gaming!");

        std::shared_ptr<GameLayer> gameLayer = std::make_shared<GameLayer>();

        AddLayer(gameLayer);
    };

    void GameLayer::OnUpdate()
    {
        UE_LOGGER("Updating!");
        glm::vec3 position = { 0.3f, 0.3f, -1.3f };
        VoxelRenderer3D::DrawBlock(position);
    }
}