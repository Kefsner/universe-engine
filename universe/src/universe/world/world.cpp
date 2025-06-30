#include "pch.hpp"

#include "universe/renderer/renderer2D.hpp"
#include "universe/world/world.hpp"
#include "universe/base/logger.hpp"

namespace Universe
{
    World::World()
    {
        m_GrassTexture = Texture2D::Create("universe/assets/textures/grass_tile.png");
        m_DirtTexture = Texture2D::Create("universe/assets/textures/dirt_tile.png");
        m_StoneTexture = Texture2D::Create("universe/assets/textures/stone_tile.png");
        m_WaterTexture = Texture2D::Create("universe/assets/textures/water_tile.png");

        UE_CORE_INFO("Generating world with dimensions: {0}x{1}", m_WorldWidth, m_WorldHeight);
        GenerateWorld();
    }

    void World::GenerateWorld()
    {
        for (int x = - m_WorldWidth / 2; x < m_WorldWidth / 2; ++x)
        {
            for (int y = -m_WorldHeight / 2; y < m_WorldHeight / 2; ++y)
            {
                Tile& tile = GetTile(x, y);
                tile.type = TileType::Grass;
            }
        }
    }

    void World::Render()
    {
        for (int x = -m_WorldWidth / 2; x < m_WorldWidth / 2; ++x)
        {
            for (int y = -m_WorldHeight / 2; y < m_WorldHeight / 2; ++y)
            {
                const Tile& tile = GetTile(x, y);
                switch (tile.type)
                {
                    case TileType::Grass:
                        Renderer2D::DrawQuad({ x, y }, { 1, 1 }, { 1, 1, 1, 1 }, m_GrassTexture);
                        break;
                    case TileType::Dirt:
                        Renderer2D::DrawQuad({ x, y }, { 1, 1 }, { 1, 1, 1, 1 }, m_DirtTexture);
                        break;
                    case TileType::Stone:
                        Renderer2D::DrawQuad({ x, y }, { 1, 1 }, { 1, 1, 1, 1 }, m_StoneTexture);
                        break;
                    case TileType::Water:
                        Renderer2D::DrawQuad({ x, y }, { 1, 1 }, { 1, 1, 1, 1 }, m_WaterTexture);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
