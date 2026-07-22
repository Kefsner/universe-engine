#include "renderer/Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Universe
{
    Camera::Camera(glm::vec3 position)
        : m_Position(position)
    {
        m_View = glm::lookAt(position, position + m_CameraFront, m_UpVector);
        m_Projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
    }

    void Camera::SetPosition(glm::vec3 position)
    {
        m_Position = position;
        m_View = glm::lookAt(m_Position, m_Position + m_CameraFront, m_UpVector);
    }

    void Camera::SetOrientation(float pitch, float yaw)
    {
    }
}