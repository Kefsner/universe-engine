#include "Application.hpp"
#include "core/Logger.hpp"

#include "core/Input.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Universe
{
    bool Input::IsKeyPressed(Key key)
    {
        Application* app = Application::Get();
        GLFWwindow* nativeWindow = app->GetWindow().GetNativeWindow();
        int state = glfwGetKey(nativeWindow, static_cast<int>(key));
        return state == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(MouseButton MouseButton)
    {
        Application* app = Application::Get();
        GLFWwindow* nativeWindow = app->GetWindow().GetNativeWindow();
        int state = glfwGetMouseButton(nativeWindow, static_cast<int>(MouseButton));
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePos()
    {
        Application* app = Application::Get();
        GLFWwindow* nativeWindow = app->GetWindow().GetNativeWindow();
        double xPos, yPos;
        glfwGetCursorPos(nativeWindow, &xPos, &yPos);
        return glm::vec2({xPos, yPos});
    }

    void Input::DisableCursor(bool disabled)
    {
        Application* app = Application::Get();
        GLFWwindow* nativeWindow = app->GetWindow().GetNativeWindow();
        int mode = disabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
        glfwSetInputMode(nativeWindow, GLFW_CURSOR, mode);
    }
}