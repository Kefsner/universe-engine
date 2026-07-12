#include "core/ImGuiLayer.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <spdlog/spdlog.h>

#include <string>

namespace Universe
{
    ImGuiLayer::ImGuiLayer(const Window& window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        ImGui_ImplGlfw_InitForOpenGL(window.GetNativeWindow(), true);
        ImGui_ImplOpenGL3_Init();

        spdlog::info("ImGuiLayer initialized");
    }

    void ImGuiLayer::Draw()
    {
        ImGui::Begin("Hello, Universe!");
        ImGui::End();
    }
    
    void ImGuiLayer::BeginFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::EndFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}