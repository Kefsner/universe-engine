#include "pch.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "universe/base/assert.hpp"
#include "universe/application.hpp"
#include "universe/renderer/opengl/opengl_graphics_context.hpp"

namespace Universe
{
    OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window)
        : m_Window(window)
    {
        glfwMakeContextCurrent(m_Window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }

    void OpenGLGraphicsContext::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }

    void OpenGLGraphicsContext::UpdateViewport()
    {
        Application& app = Application::Get();
        float width = app.GetWindow().GetWidth();
        float height = app.GetWindow().GetHeight();
        glViewport(0, 0, width, height);
    }
}