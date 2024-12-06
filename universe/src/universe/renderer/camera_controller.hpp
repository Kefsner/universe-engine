#pragma once

#include "universe/core/timestep.hpp"
#include "universe/renderer/camera.hpp"
#include "universe/events/application_event.hpp"
#include "universe/events/mouse_event.hpp"

namespace Universe {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio);
        ~OrthographicCameraController() = default;

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        // Getters
        OrthographicCamera& getCamera() { return m_Camera; }
        const OrthographicCamera& getCamera() const { return m_Camera; }

    private:
        float m_AspectRatio;                                // Aspect ratio of the camera
        float m_ZoomLevel = 1.0f;                           // Zoom level of the camera
        OrthographicCamera m_Camera;                        // Orthographic camera
        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };  // Camera position
        float m_CameraTranslationSpeed = 1.0f;              // Camera translation speed

        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    };

}
