#include "pch.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "universe/base/logger.hpp"
#include "universe/base/assert.hpp"
#include "universe/window/window.hpp"
#include "universe/window/glfw_window.hpp"

namespace Universe
{
    GLFWWindowWrapper::GLFWWindowWrapper(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

        m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

        m_Context = GraphicsContext::Create(m_Window);
    }

    GLFWWindowWrapper::~GLFWWindowWrapper()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void GLFWWindowWrapper::OnUpdate()
    {
        m_Context->SwapBuffers();
    }
}