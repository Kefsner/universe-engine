#pragma once

#include "universe/base/base.hpp"
#include "universe/base/timestep.hpp"
#include "universe/renderer/texture.hpp"
#include "universe/renderer/renderer2D.hpp"

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
        void Render();

    private:
        static constexpr int m_WorldWidth = 100;
        static constexpr int m_WorldHeight = 100;

        enum class TileType
        {
            Air = 0,
            Dirt,
            Grass,
            Water,
            Stone
        };

        struct Tile
        {
            TileType type = TileType::Air;
        };

        std::array<Tile, m_WorldWidth * m_WorldHeight> m_Tiles;

        Ref<Texture2D> m_GrassTexture;
        Ref<Texture2D> m_DirtTexture;
        Ref<Texture2D> m_StoneTexture;
        Ref<Texture2D> m_WaterTexture;

        Tile& GetTile(int x, int y)
        {
            x += m_WorldWidth / 2;
            y += m_WorldHeight / 2;
            return m_Tiles[y * m_WorldWidth + x];
        }

        const Tile& GetTile(int x, int y) const
        {
            x += m_WorldWidth / 2;
            y += m_WorldHeight / 2;
            return m_Tiles[y * m_WorldWidth + x];
        }
    };
}
