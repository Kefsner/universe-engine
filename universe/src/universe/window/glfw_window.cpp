#include "pch.hpp"

#include "universe/window/glfw_window.hpp" // Includes GLFW/glfw3.h
#include "universe/renderer/graphics_context.hpp"
#include "universe/events/key_event.hpp"
#include "universe/events/mouse_event.hpp"
#include "universe/events/application_event.hpp"

namespace Universe {

    static bool s_GLFWInitialized = false; // Static variable to check if GLFW is initialized

    GLFWWindowWrapper::GLFWWindowWrapper(const WindowProps& props)
    {
        // Initialize the window data from the WindowProps
        m_WindowData.Title  = props.Title;
        m_WindowData.Width  = props.Width;
        m_WindowData.Height = props.Height;
        m_WindowData.VSync  = props.VSync;

        // Initialize GLFW if it is not already initialized
        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            // UE_CORE_ASSERT(success, "Could not initialize GLFW!");
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)m_WindowData.Width, (int)m_WindowData.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
        // UE_CORE_ASSERT(m_Window, "Could not create window!");

        m_Context = GraphicsContext::Create(m_Window); // Returns an OpenGL context for now
        m_Context->Init();                             //Has glfw calls
        SetVSync(m_WindowData.VSync);
        glfwSetWindowUserPointer(m_Window, &m_WindowData);
        SetCallbacks();
    }

    GLFWWindowWrapper::~GLFWWindowWrapper() {
        glfwDestroyWindow(m_Window);
    }

    void GLFWWindowWrapper::OnUpdate()
    {
        m_Context->SwapBuffers();
        glfwPollEvents();
    }

    void GLFWWindowWrapper::SetCallbacks()
    {
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowResizeEvent event(width, height);
            data.Width = width;
            data.Height = height;
            data.EventCallback(event);
        });
        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
            }
        });
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });
        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
    } 
}
