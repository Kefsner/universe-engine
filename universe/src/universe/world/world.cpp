#include "pch.hpp"

#include "universe/renderer/renderer2D.hpp"
#include "universe/world/world.hpp"
#include "universe/base/logger.hpp"

namespace Universe
{
    World::World()
    {
        for (auto& tile : m_Tiles)
        {
            tile.type = TileType::Dirt;
        }
    }

    void World::GenerateWorld()
    {
        // Simple world generation logic
        for (int x = 0; x < WorldWidth; ++x)
        {
            for (int y = 0; y < WorldHeight; ++y)
            {
                Tile& tile = m_Tiles[y * WorldWidth + x];

                Renderer2D::DrawQuad({ static_cast<float>(x), static_cast<float>(y) }, { .9f, .9f }, { 0.5f, 0.5f, 0.5f, 1.0f });
            }
        }
    }
}
