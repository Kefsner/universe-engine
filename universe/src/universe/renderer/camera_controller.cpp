#include "pch.hpp"

#include "universe/core/core.hpp"
#include "universe/core/logger.hpp"
#include "universe/renderer/camera_controller.hpp"
#include "universe/input/key_codes.hpp"
#include "universe/input/mouse_button_codes.hpp"
#include "universe/input/input.hpp"

namespace Universe {

    OrthographicCameraController::OrthographicCameraController(float aspectRatio)
        : m_AspectRatio(aspectRatio),
        m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel) {}

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if (Input::IsKeyPressed(UE_KEY_A) && Input::IsKeyPressed(UE_KEY_D)) {}
        else if (Input::IsKeyPressed(UE_KEY_A)) {
            m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(UE_KEY_D)) {
            m_CameraPosition.x += m_CameraTranslationSpeed * ts;
        }

        if (Input::IsKeyPressed(UE_KEY_W) && Input::IsKeyPressed(UE_KEY_S)) {}
        else if (Input::IsKeyPressed(UE_KEY_W)) {
            m_CameraPosition.y += m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(UE_KEY_S)) {
                    m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
        }

        m_CameraTranslationSpeed = m_ZoomLevel;
        
        m_Camera.SetPosition(m_CameraPosition);
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(UE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

}
