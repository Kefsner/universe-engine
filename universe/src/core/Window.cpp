#include "core/Logger.hpp"
#include "core/Window.hpp"
#include "events/KeyEvents.hpp"
#include "events/MouseEvents.hpp"
#include "events/WindowEvents.hpp"

#include <cassert>

#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace Universe
{
    void Window::DebugCallbackMessage(
        GLenum Source,
        GLenum Type,
        GLuint Id,
        GLenum Severity,
        GLsizei Length,
        const GLchar* Message,
        const void* UserParam
    )
    {
        switch (Severity)
        {
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                break;
            case GL_DEBUG_SEVERITY_LOW:
                spdlog::warn("OpenGL DebugCallback:");
                spdlog::warn("  --Severity Low: {}", Message);
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                spdlog::warn("OpenGL DebugCallback:");
                spdlog::warn("  --Severity Medium: {}", Message);
                break;
            case GL_DEBUG_SEVERITY_HIGH:
                spdlog::error("OpenGL DebugCallback:");
                spdlog::error(" --Severity High: {}", Message);
                assert(false);
                break;
            default:
                break;
        }
    }

    Window::Window(WindowProps props)
        : m_Props(props)
    {
        if (!glfwInit())
        {
            spdlog::error("Failed to initialize GLFW.");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, props.Debug ? GLFW_TRUE : GLFW_FALSE);

        m_NativeWindow = glfwCreateWindow(
            props.Width, props.Height, props.Title, nullptr, nullptr
        );

        if (!m_NativeWindow)
        {
            glfwTerminate();
            spdlog::error("Failed to create a window.");
        }

        UE_CORE_INFO("Window created successfully.");
       
        int glfwVersionMajor, glfwVersionMinor;
        glfwGetVersion(&glfwVersionMajor, &glfwVersionMinor, nullptr);

        UE_CORE_INFO("  --GLFW Version Major {}", glfwVersionMajor);
        UE_CORE_INFO("  --GLFW Version Minor {}", glfwVersionMinor);
        m_DebugMode = glfwGetWindowAttrib(m_NativeWindow, GLFW_CONTEXT_DEBUG);
        if (m_DebugMode)
            UE_CORE_INFO("  --GLFW debug mode on.");

        glfwMakeContextCurrent(m_NativeWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            spdlog::error("Failed to initialize GLAD.");
        }

        UE_CORE_INFO("GLAD initialized successfully.");

        int glVersionMajor, glVersionMinor;
        
        glGetIntegerv(GL_MAJOR_VERSION, &glVersionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &glVersionMinor);

        UE_CORE_INFO("  --OpenGL Version Major {}", glVersionMajor);
        UE_CORE_INFO("  --OpenGL Version Minor {}", glVersionMinor);

        int  glProfile;
        glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &glProfile);
        switch (glProfile)
        {
        case GL_CONTEXT_CORE_PROFILE_BIT:
            UE_CORE_INFO("  --OpenGL Core Profile");
            break;
        case GL_CONTEXT_COMPATIBILITY_PROFILE_BIT:
            UE_CORE_INFO("  --OpenGL Compatibility Profile");
            break;
        default:
            spdlog::error("Unkown OpenGL Profile");
            assert(false);
            break;
        }

        if (m_DebugMode)
        {
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(Window::DebugCallbackMessage, 0);
            UE_CORE_INFO("  --OpenGL debug synchronous output mode on.");
        }

        glViewport(0, 0, props.Width, props.Height);

        glfwSetWindowUserPointer(m_NativeWindow, this);
        SetEventCallbacks();
    }

    Window::~Window()
    {
        glfwTerminate();
        glfwDestroyWindow(m_NativeWindow);
    }

    void Window::SetEventCallbackFn(EventCallbackFn callback)
    {
        m_EventCallbackFn = std::move(callback);
    }

    void Window::Update()
    {
        glfwSwapBuffers(m_NativeWindow);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::OnResize(int width, int height)
    {
        m_Props.Width = width;
        m_Props.Height = height;

        glViewport(0, 0, width, height);
    }

    void Window::SetEventCallbacks()
    {
        
        glfwSetKeyCallback(
            m_NativeWindow, [](GLFWwindow* nativeWindow, int key, int scancode, int action, int mods)
            {
                switch (action)
                {
                case GLFW_PRESS:
                {
                    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

                    KeyPressEvent event(key);
                    window->m_EventCallbackFn(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

                    KeyReleaseEvent event(key);
                    window->m_EventCallbackFn(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

                    KeyRepeatEvent event(key);
                    window->m_EventCallbackFn(event);
                    break;
                }
                default:
                    break;
                }
            }
        );
        
        glfwSetCursorPosCallback(
            m_NativeWindow, [](GLFWwindow* nativeWindow, double xpos, double ypos)
            {
                Window* window = static_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

                MouseMoveEvent event(xpos, ypos);
                window->m_EventCallbackFn(event);
            }
        );

        glfwSetMouseButtonCallback(
            m_NativeWindow, [](GLFWwindow* nativeWindow, int button, int action, int mods)
            {
                Window* window = static_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

                MouseButtonEvent event(button);
                window->m_EventCallbackFn(event); 
            }
        );

        glfwSetScrollCallback(
            m_NativeWindow, [](GLFWwindow* nativeWindow, double xoffset, double yoffset)
            {
                Window* window = static_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

                MouseScrollEvent event(yoffset);
                window->m_EventCallbackFn(event); 
            }
        );

        glfwSetWindowSizeCallback(
            m_NativeWindow, [](GLFWwindow* nativeWindow, int width, int height)
            {
                Window* window = static_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

                WindowResizeEvent event(width, height);
                window->m_EventCallbackFn(event);
            }
        );

        glfwSetWindowCloseCallback(
            m_NativeWindow, [](GLFWwindow* nativeWindow)
            {
                Window* window = static_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

                WindowCloseEvent event;
                window->m_EventCallbackFn(event);
            }
        );
    }
}