#include "Shader.hpp"
#include "Window.hpp"

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

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bottom left
         0.5f, -0.5f, 0.0f, // Bottom right
         0.5f,  0.5f, 0.0f, // Top right
         -0.5f, 0.5f, 0.0f  // Top left
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    GLuint vertexBuffer, indexBuffer;
    glCreateBuffers(1, &indexBuffer);
    glCreateBuffers(1, &vertexBuffer);

    glNamedBufferData(vertexBuffer, 12*sizeof(float), vertices, GL_STATIC_DRAW);
    glNamedBufferData(indexBuffer, 6*sizeof(unsigned int), indices, GL_STATIC_DRAW);

    GLuint vertexArray;
    glCreateVertexArrays(1, &vertexArray);

    glVertexArrayVertexBuffer(vertexArray, 0, vertexBuffer, 0, 3*sizeof(float));
    glVertexArrayElementBuffer(vertexArray, indexBuffer);

    int attributeIndex = 0; // This is the shader attribute location
    int bidingIndex = 0;
    int attributeSize = 3;
    glEnableVertexArrayAttrib(vertexArray, attributeIndex);
    glVertexArrayAttribFormat(vertexArray, attributeIndex, attributeSize, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vertexArray, attributeIndex, bidingIndex);

    glBindVertexArray(vertexArray);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        window.Update();
    }

    glfwTerminate();

    return 0;
}