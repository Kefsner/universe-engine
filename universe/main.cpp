#include "Shader.hpp"
#include "Window.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

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
    Universe::Shader shader = Universe::Shader();

    Universe::VertexBuffer vertexBuffer = Universe::VertexBuffer();
    Universe::IndexBuffer indexBuffer = Universe::IndexBuffer();
    Universe::VertexArray vertexArray = Universe::VertexArray();

    vertexArray.AttachBuffers(&vertexBuffer, &indexBuffer);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init();

    while (!window.ShouldClose())
    {
        
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        shader.Bind();
        vertexArray.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        window.Update();
    }

    glfwTerminate();

    return 0;
}