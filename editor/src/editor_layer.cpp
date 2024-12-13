#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "pch.hpp"
#include "editor_layer.hpp"

namespace Universe {

    EditorLayer::EditorLayer() : m_CameraController(1280.0f / 720.0f)
    {
    }

    void EditorLayer::OnAttach()
    {
        FramebufferSpecification fbSpec;
        fbSpec.width = 1280;
        fbSpec.height = 720;
        m_Framebuffer = Framebuffer::Create(fbSpec);

        m_GrassTexture = Texture2D::Create("editor/assets/textures/grass.png");
    }

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        m_CameraController.OnUpdate(ts);

        RenderCommand::SetClearColor({0.8f, 0.2f, 0.3f, 1.0f}); // Set the clear color to pink
        RenderCommand::Clear();

        m_Framebuffer->Bind();

        RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        RenderCommand::Clear();

        Renderer2D::BeginScene(m_CameraController.GetCamera());
        Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_Color);
        Renderer2D::DrawQuad({1.0f, 0.0f}, {2.0f, 2.0f}, m_GrassTexture, 1.0f, m_Color);
        Renderer2D::EndScene();

        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnEvent(Event& e)
    {
        m_CameraController.OnEvent(e);
    }

    void EditorLayer::OnImGuiRender()
    {
        ImGui::Begin("Viewport");
        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2{1280.0f, 720.0f}, ImVec2{0, 1}, ImVec2{1, 0});
        ImGui::End();
    }

}