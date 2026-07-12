#include "core/Window.hpp"
#include "core/ImGuiLayer.hpp"
#include "renderer/Renderer.hpp"

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

    while (!window.ShouldClose())
    {
        renderer.DrawSprite();

        imGuiLayer.BeginFrame();
        imGuiLayer.Draw();
        imGuiLayer.EndFrame();

        window.Update();
    }

    glfwTerminate();

    return 0;
}