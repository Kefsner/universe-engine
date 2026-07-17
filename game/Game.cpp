#include "Game.hpp"

namespace Universe
{
    Game::Game()
    {
        UE_LOGGER("Gaming!");
    };
}

// int main()
// {
//     spdlog::info("Welcome to spdlog!");

//     Universe::WindowProps windowProps{
//         .Width = 1920,
//         .Height = 1080,
//         .Title = "Hello, Universe!",
//         .Debug = false
//     };
// #ifdef UNIVERSE_DEBUG
//     windowProps.Debug = true;
// #endif

//     Universe::Window window = Universe::Window(windowProps);
//     Universe::Renderer renderer = Universe::Renderer();
//     Universe::ImGuiLayer imGuiLayer = Universe::ImGuiLayer(window);

//     std::shared_ptr<Universe::Texture> texture = Universe::AssetManager::LoadTexture("assets/blocks.png");

//     while (!window.ShouldClose())
//     {
//         renderer.DrawCube(texture, 1, {0.0f, 0.0f, 0.0f});
//         imGuiLayer.BeginFrame();
//         imGuiLayer.Draw();
//         imGuiLayer.EndFrame();

//         window.Update();
//     }

//     glfwTerminate();

//     return 0;
// }