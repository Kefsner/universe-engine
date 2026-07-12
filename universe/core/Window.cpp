#include "Window.hpp"

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

        spdlog::info("Window created successfully.");
       
        int glfwVersionMajor, glfwVersionMinor;
        glfwGetVersion(&glfwVersionMajor, &glfwVersionMinor, nullptr);

        spdlog::info("  --GLFW Version Major {}", glfwVersionMajor);
        spdlog::info("  --GLFW Version Minor {}", glfwVersionMinor);
        m_DebugMode = glfwGetWindowAttrib(m_NativeWindow, GLFW_CONTEXT_DEBUG);
        if (m_DebugMode)
            spdlog::info("  --GLFW debug mode on.");

        glfwMakeContextCurrent(m_NativeWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            spdlog::error("Failed to initialize GLAD.");
        }

        spdlog::info("GLAD initialized successfully.");

        int glVersionMajor, glVersionMinor;
        
        glGetIntegerv(GL_MAJOR_VERSION, &glVersionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &glVersionMinor);

        spdlog::info("  --OpenGL Version Major {}", glVersionMajor);
        spdlog::info("  --OpenGL Version Minor {}", glVersionMinor);

        int  glProfile;
        glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &glProfile);
        switch (glProfile)
        {
        case GL_CONTEXT_CORE_PROFILE_BIT:
            spdlog::info("  --OpenGL Core Profile");
            break;
        case GL_CONTEXT_COMPATIBILITY_PROFILE_BIT:
            spdlog::info("  --OpenGL Compatibility Profile");
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
            spdlog::info("  --OpenGL debug synchronous output mode on.");
        }

        glViewport(0, 0, props.Width, props.Height);
    }

    Window::~Window()
    {
        glfwTerminate();
        glfwDestroyWindow(m_NativeWindow);
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(m_NativeWindow);
    }

    void Window::Update()
    {
        glfwSwapBuffers(m_NativeWindow);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
    }
}