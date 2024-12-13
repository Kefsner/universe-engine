#pragma once

#include "universe.hpp"

namespace Universe {

    class EditorLayer : public Layer {
    public:
        EditorLayer();
        virtual ~EditorLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        virtual void OnUpdate(Timestep ts) override;
        virtual void OnEvent(Event& event) override;
        virtual void OnImGuiRender() override;

    private:
        OrthographicCameraController m_CameraController;

        Ref<Universe::Texture2D> m_GrassTexture;
        glm::vec4 m_Color = { 0.2f, 0.3f, 0.8f, 1.0f };

        // Temp
        Ref<VertexArray> m_SquareVA;
        Ref<Shader> m_FlatColorShader;
        Ref<Framebuffer> m_Framebuffer;
    };
}