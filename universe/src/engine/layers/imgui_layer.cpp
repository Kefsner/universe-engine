#include "pch.hpp"
#include "engine/layers/imgui_layer.hpp"
#include "engine/events/event.hpp"
#include "engine/application.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Universe {
    
    ImGuiLayer::ImGuiLayer() {}
    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::OnAttach()
	{
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        Application& app = Application::Get();
        Window& window = app.GetWindow();
        GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(window.GetNativeWindow());
        ImGui_ImplGlfw_InitForOpenGL(nativeWindow, true);
        ImGui_ImplOpenGL3_Init("#version 410");
	}

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    
    void ImGuiLayer::OnUpdate()
    {
        UE_CORE_ERROR("ImGuiLayer::OnUpdate");
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& event) {}
}