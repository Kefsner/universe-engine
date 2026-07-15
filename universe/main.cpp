#include "core/Window.hpp"
#include "core/ImGuiLayer.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/Texture.hpp"
#include "core/AssetManager.hpp"
#include "core/OrthographicCamera.hpp"

#include <iostream>

#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main()
{
    spdlog::info("Welcome to spdlog!");

    Universe::WindowProps windowProps{
        .Width = 1920,
        .Height = 1080,
        .Title = "Hello, Universe!",
        .Debug = false
    };
#ifdef UNIVERSE_DEBUG
    windowProps.Debug = true;
#endif

    Universe::Window window = Universe::Window(windowProps);
    Universe::Renderer renderer = Universe::Renderer();
    Universe::ImGuiLayer imGuiLayer = Universe::ImGuiLayer(window);

    Universe::OrthographicCamera orthoCam = Universe::OrthographicCamera(windowProps.Width, windowProps.Height);
    
    std::shared_ptr<Universe::Texture> textureSlime = Universe::AssetManager::LoadTexture("assets/slime.png");
    std::shared_ptr<Universe::Texture> textureSlimeIdle = Universe::AssetManager::LoadTexture("assets/slime-idle.png");
    std::shared_ptr<Universe::Texture> textureTilemap = Universe::AssetManager::LoadTexture("assets/tilemap.png");

    while (!window.ShouldClose())
    {
        renderer.DrawSprite(textureSlime, {0.0f, 0.0f, 0.0f});
        renderer.DrawSprite(textureSlimeIdle, {0.0f, 0.0f, 0.0f});
        renderer.DrawSprite(textureTilemap, {0.5f, 0.0f, 0.0f});

        imGuiLayer.BeginFrame();
        imGuiLayer.Draw();
        imGuiLayer.EndFrame();

        window.Update();
    }

    glfwTerminate();

    return 0;
}