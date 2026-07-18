#include "Game.hpp"

#include "GameLayer.hpp"

namespace Universe
{
    Game::Game()
    {
        UE_INFO("Gaming!");

        std::shared_ptr<GameLayer> gameLayer = std::make_shared<GameLayer>();

        AddLayer(gameLayer);
    };
}