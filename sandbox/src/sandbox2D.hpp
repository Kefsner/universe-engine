#pragma once

#include <universe.hpp>

class Sandbox2D : public Universe::Layer
{
public:
    Sandbox2D()
        : m_AssetManager(Universe::AssetManager::GetInstance()) {}
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;

private:
    Universe::OrthographicCamera m_Camera;
    Universe::Ref<Universe::Scene> m_Scene;

    Universe::AssetManager& m_AssetManager;
    
    Universe::Entity m_Player;
    float m_MoveSpeed = 5.0f;
    float m_RunningSpeed = 10.0f;
    bool m_FacingRight = true;

    Universe::Entity m_Rock;
};

// class World
// {
// public:
//     World();
//     ~World() = default;

//     static Ref<World> Create()
//     {
//         return CreateRef<World>();
//     }

//     void GenerateWorld();
//     void Render();

// private:
//     static constexpr int m_WorldWidth = 100;
//     static constexpr int m_WorldHeight = 100;

//     enum class TileType
//     {
//         Air = 0,
//         Dirt,
//         Grass,
//         Water,
//         Stone
//     };

//     struct Tile
//     {
//         TileType type = TileType::Air;
//     };

//     std::array<Tile, m_WorldWidth * m_WorldHeight> m_Tiles;

//     Ref<Texture2D> m_GrassTexture;
//     Ref<Texture2D> m_DirtTexture;
//     Ref<Texture2D> m_StoneTexture;
//     Ref<Texture2D> m_WaterTexture;

//     Tile& GetTile(int x, int y)
//     {
//         x += m_WorldWidth / 2;
//         y += m_WorldHeight / 2;
//         return m_Tiles[y * m_WorldWidth + x];
//     }

//     const Tile& GetTile(int x, int y) const
//     {
//         x += m_WorldWidth / 2;
//         y += m_WorldHeight / 2;
//         return m_Tiles[y * m_WorldWidth + x];
//     }
// };

// World::World()
//     {
//         m_GrassTexture = Texture2D::Create("universe/assets/textures/grass_tile.png");
//         m_DirtTexture = Texture2D::Create("universe/assets/textures/dirt_tile.png");
//         m_StoneTexture = Texture2D::Create("universe/assets/textures/stone_tile.png");
//         m_WaterTexture = Texture2D::Create("universe/assets/textures/water_tile.png");

//         UE_CORE_INFO("Generating world with dimensions: {0}x{1}", m_WorldWidth, m_WorldHeight);
//         GenerateWorld();
//     }

//     void World::GenerateWorld()
//     {
//         for (int x = - m_WorldWidth / 2; x < m_WorldWidth / 2; ++x)
//         {
//             for (int y = -m_WorldHeight / 2; y < m_WorldHeight / 2; ++y)
//             {
//                 Tile& tile = GetTile(x, y);
//                 tile.type = TileType::Grass;
//             }
//         }
//     }

//     void World::Render()
//     {
//         for (int x = -m_WorldWidth / 2; x < m_WorldWidth / 2; ++x)
//         {
//             for (int y = -m_WorldHeight / 2; y < m_WorldHeight / 2; ++y)
//             {
//                 const Tile& tile = GetTile(x, y);
//                 switch (tile.type)
//                 {
//                     case TileType::Grass:
//                         Renderer2D::DrawQuad({ x, y }, { 1, 1 }, { 1, 1, 1, 1 }, m_GrassTexture);
//                         break;
//                     case TileType::Dirt:
//                         Renderer2D::DrawQuad({ x, y }, { 1, 1 }, { 1, 1, 1, 1 }, m_DirtTexture);
//                         break;
//                     case TileType::Stone:
//                         Renderer2D::DrawQuad({ x, y }, { 1, 1 }, { 1, 1, 1, 1 }, m_StoneTexture);
//                         break;
//                     case TileType::Water:
//                         Renderer2D::DrawQuad({ x, y }, { 1, 1 }, { 1, 1, 1, 1 }, m_WaterTexture);
//                         break;
//                     default:
//                         break;
//                 }
//             }
//         }
//     }