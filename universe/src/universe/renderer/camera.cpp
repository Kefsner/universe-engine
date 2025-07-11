#include "pch.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "universe/base/base.hpp"
#include "universe/renderer/camera.hpp"
#include "universe/events/events.hpp"
#include "universe/events/mouse_events.hpp"
#include "universe/events/application_events.hpp"
#include "universe/inputs/input.hpp"

namespace Universe
{
    OrthographicCamera::OrthographicCamera(float width, float height)
        : m_ZoomLevel(10.f), m_ViewMatrix(1.0f)
    {
        SetViewportSize(width, height);

        RecalculateViewMatrix();
    }

    void OrthographicCamera::OnUpdate(Timestep ts)
    {

    }

    void OrthographicCamera::SetViewportSize(float width, float height)
    {
        m_AspectRatio = width / height;
        m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(UE_BIND_EVENT_FN(OrthographicCamera::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(OrthographicCamera::OnWindowResized));
    }

    bool OrthographicCamera::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel += e.GetMouseYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

        return false;
    }

    bool OrthographicCamera::OnWindowResized(WindowResizeEvent& e)
    {
        SetViewportSize(e.GetWidth(), e.GetHeight());

        return false;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_CameraPosition) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation), glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}