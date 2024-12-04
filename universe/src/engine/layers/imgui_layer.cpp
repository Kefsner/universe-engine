#include "pch.hpp"
#include "engine/application.hpp"

#include "engine/layers/imgui_layer.hpp"
#include <imgui.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

namespace Universe {

    void ImGuiLayer::OnAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        Application& app = Application::Get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGuiIO& io = ImGui::GetIO();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::OnImGuiRender() {
        static bool show = true;
        ImGuiLayer::ShowPerformanceMetrics(&show);
    }

    void ImGuiLayer::ShowPerformanceMetrics(bool* p_open) {
        if (!p_open) return;
        // Track min/max FPS and FPS history
        static float fpsHistory[100] = { 0.0f };
        static int historyIndex = 0;
        static float minFPS = FLT_MAX;
        static float maxFPS = 0.0f;

        float currentFPS = ImGui::GetIO().Framerate;
        fpsHistory[historyIndex] = currentFPS;
        historyIndex = (historyIndex + 1) % IM_ARRAYSIZE(fpsHistory);

        // Update min/max FPS
        if (currentFPS < minFPS) minFPS = currentFPS;
        if (currentFPS > maxFPS) maxFPS = currentFPS;

        // Calculate 1% FPS (average of the lowest 1% of recorded FPS values)
        float onePercentFPS = 0.0f;
        int onePercentCount = static_cast<int>(IM_ARRAYSIZE(fpsHistory) * 0.01f);
        onePercentCount = (onePercentCount > 0) ? onePercentCount : 1; // Ensure at least one frame is included

        // Copy and sort the FPS history
        float sortedFPS[IM_ARRAYSIZE(fpsHistory)];
        memcpy(sortedFPS, fpsHistory, sizeof(fpsHistory));
        std::sort(sortedFPS, sortedFPS + IM_ARRAYSIZE(sortedFPS)); // Sort ascending

        // Calculate the average of the lowest 1%
        for (int i = 0; i < onePercentCount; ++i) {
            onePercentFPS += sortedFPS[i];
        }
        onePercentFPS /= onePercentCount;

        // Begin the overlay window
        ImGui::Begin("Performance Overlay");
        // Display current FPS and frame time
        ImGui::Text("FPS: %.1f", currentFPS);
        ImGui::Text("Frame Time: %.3f ms", 1000.0f / currentFPS);

        // Display min/max FPS
        ImGui::Text("Min FPS: %.1f", minFPS);
        ImGui::Text("Max FPS: %.1f", maxFPS);

        // Display 1% FPS
        ImGui::Text("1%% FPS: %.1f", onePercentFPS); // Double '%' for formatting in ImGui

        // Plot FPS history
        ImGui::PlotLines("FPS History", fpsHistory, IM_ARRAYSIZE(fpsHistory), 0, nullptr, 0.0f, maxFPS, ImVec2(0, 80));

        // End the overlay window
        ImGui::End();
    }

}