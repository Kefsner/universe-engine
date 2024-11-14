#include "engine/window/glfw_window.hpp"
#include "engine/logger/logger.hpp"

namespace Universe {
    static bool s_GLFWInitialized;
    GLFWWindow::GLFWWindow(const WindowProps& props) {
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
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        UE_CORE_ASSERT(status, "Could not initialize Glad!");

		UE_CORE_INFO("OpenGL Info:");
		UE_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		UE_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		UE_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

		UE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Universe requires at least OpenGL version 4.5!");
	}

    GLFWWindow::~GLFWWindow() {
        glfwDestroyWindow(m_Window);
    }

    void GLFWWindow::OnUpdate() {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    Window* Window::Create(const WindowProps& props) {
        return new GLFWWindow(props);
    }
}
