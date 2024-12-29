#pragma once

#include <glm/glm.hpp>

#include "universe/base/timestep.hpp"
#include "universe/events/events.hpp"
#include "universe/events/mouse_events.hpp"
#include "universe/events/application_events.hpp"

namespace Universe
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera() = default;
        OrthographicCamera(float width, float height);

        void AttachDefaultController(float speed = 1.0f)
        {
            m_ControllerEnabled = true;
            m_ControllerSpeed = speed;
        };

        void DetachController() { m_ControllerEnabled = false; };

        void OnUpdate(Timestep ts);

        void SetViewportSize(float width, float height);

        void OnEvent(Event& e);
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

        void SetPosition(const glm::vec3& position) { m_CameraPosition = position; RecalculateViewMatrix(); }
        const glm::vec3& GetPosition() const { return m_CameraPosition; }

        void SetRotation(float rotation) { m_CameraRotation = rotation; RecalculateViewMatrix(); }
        float GetRotation() const { return m_CameraRotation; }

        void RecalculateViewMatrix();

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    private:
        float m_AspectRatio;
        float m_ZoomLevel;

        bool m_ControllerEnabled = false;
        float m_ControllerSpeed = 1.0f;

        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f;

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
    };
}