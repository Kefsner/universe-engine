#pragma once

#include "universe/base/base.hpp"
#include "universe/base/timestep.hpp"
#include <array>

namespace Universe
{
    class World
    {
    public:
        World();
        ~World() = default;
        
        static Ref<World> Create()
        {
            return CreateRef<World>();
        }

        void GenerateWorld();

    private:
        static constexpr int WorldWidth = 100;
        static constexpr int WorldHeight = 100;

        enum class TileType
        {
            Air = 0,
            Dirt,
            Grass,
            Stone
        };

        struct Tile
        {
            TileType type = TileType::Air;
        };

        std::array<Tile, WorldWidth * WorldHeight> m_Tiles;
    };
}
