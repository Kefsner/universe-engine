#pragma once

#include <glm/glm.hpp>

namespace Universe
{
    class Camera
    {
    public:
        Camera(glm::vec3 position);
        ~Camera() = default;

        void SetPosition(glm::vec3 position);
        void SetOrientation(float pitch, float yaw);

        glm::vec3 GetPosition() const { return m_Position; }
        glm::vec3 GetCameraFront() const { return m_CameraFront; }

        glm::mat4 GetProjectionViewMatrix() const { return m_Projection * m_View; }

    private:
        glm::vec3 m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_Position;

        float m_Pitch, m_Yaw;

        glm::mat4 m_View;
        glm::mat4 m_Projection;
    };
}