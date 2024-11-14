#include "engine/window/glfw_window.hpp"
#include "engine/renderer/opengl/opengl_context.hpp"
#include "engine/logger/logger.hpp"

namespace Universe {
    static bool s_GLFWInitialized;
    UEGLFWWindow::UEGLFWWindow(const WindowProps& props) {
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

        m_Context = new OpenGLContext(m_Window);
        m_Context->Init();
	}

    UEGLFWWindow::~UEGLFWWindow() {
        glfwDestroyWindow(m_Window);
    }

    void UEGLFWWindow::OnUpdate() {
        glClear(GL_COLOR_BUFFER_BIT);
        m_Context->SwapBuffers();
        glfwPollEvents();
    }

    Window* Window::Create(const WindowProps& props) {
        return new UEGLFWWindow(props);
    }
}
