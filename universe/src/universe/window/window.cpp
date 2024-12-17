#include "pch.hpp"

#include "universe/base/base.hpp"
#include "universe/window/window.hpp"
#include "universe/window/glfw_window.hpp"

namespace Universe
{
    Scope<Window> Window::Create(const WindowProps& props)
    {
        return CreateScope<GLFWWindowWrapper>(props);
    }
}