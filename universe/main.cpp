#include "core/Window.hpp"
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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init();

    while (!window.ShouldClose())
    {
        renderer.DrawQuad();
        
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::ShowDemoWindow();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.Update();
    }

    glfwTerminate();

    return 0;
}