#pragma once
#include "engine/renderer/camera.hpp"
#include "engine/timestep.hpp"
#include "engine/events/application_event.hpp"
#include "engine/events/mouse_event.hpp"

namespace Universe {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        OrthographicCamera& getCamera() { return m_Camera; }
        const OrthographicCamera& getCamera() const { return m_Camera; }

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;
    
        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraTranslationSpeed = 1.0f;

        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    };

}
