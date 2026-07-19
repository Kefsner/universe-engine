#include "Application.hpp"
#include "core/Logger.hpp"

#include "core/Input.hpp"

#include <GLFW/glfw3.h>

namespace Universe
{
    bool Input::IsKeyPressed(Key key)
    {
        Application* app = Application::Get();
        GLFWwindow* nativeWindow = app->GetWindow().GetNativeWindow();
        int state = glfwGetKey(nativeWindow, static_cast<int>(key));
        return state == GLFW_PRESS;
    }
}