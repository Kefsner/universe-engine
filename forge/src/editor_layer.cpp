#include "pch.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "universe/application.hpp"
#include "editor_layer.hpp"

namespace Universe
{
    void EditorLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::Get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void EditorLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void EditorLayer::OnEvent(Event& event)
    {
        UE_CORE_TRACE("{0}", event.ToString());
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        
        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create Dockspace
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

        // Scene Hierarchy (Left)
        ImGui::Begin("Scene Hierarchy");
        // Add hierarchy content here (e.g., tree nodes for objects)
        ImGui::Text("GameObject1");
        ImGui::Text("GameObject2");
        ImGui::End();

        // Scene Viewer (Center)
        ImGui::Begin("Scene Viewer");
        // Render your framebuffer as a texture
        // uint32_t framebufferTexture = GetFramebufferTexture(); // Replace with your framebuffer texture ID
        //ImGui::Image((void*)(intptr_t)framebufferTexture, ImVec2(800, 600)); // Example dimensions
        ImGui::End();

        // Console (Bottom)
        ImGui::Begin("Console");
        ImGui::Text("Logs will appear here");
        ImGui::End();

        // Inspector/Properties (Right)
        ImGui::Begin("Inspector");
        ImGui::Text("Object Properties:");
        // ImGui::InputFloat3("Position", position); // Example property
        // ImGui::InputFloat3("Rotation", rotation);
        // ImGui::InputFloat3("Scale", scale);
        ImGui::End();

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}