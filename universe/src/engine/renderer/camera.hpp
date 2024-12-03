#pragma once

#include <glm/glm.hpp>

namespace Universe {

    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetProjection(float left, float right, float bottom, float top);
        
        void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
        const glm::vec3& GetPosition() const { return m_Position; }

    private:
        glm::mat4 m_ProjectionMatrix; // Projection onto the screen
        glm::mat4 m_ViewMatrix; // Camera position and rotation
        glm::mat4 m_ViewProjectionMatrix; // Projection * View
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f }; // Camera position

        void RecalculateViewMatrix();
    };
}