#include "windowsWindow.hpp"
#include "engine/core/logger/logger.hpp"

namespace Universe {
    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props) {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props) {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        if (!s_GLFWInitialized) {
            int success = glfwInit();
            UE_CORE_ASSERT(success, "Could not initialize GLFW!");
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        UE_CORE_ASSERT(m_Window, "Could not create window!");

        glfwMakeContextCurrent(m_Window);
    }

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
	}

    void WindowsWindow::OnUpdate()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}
