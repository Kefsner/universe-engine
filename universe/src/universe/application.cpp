#include "pch.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "universe/application.hpp"
#include "universe/base/logger.hpp"
#include "universe/base/assert.hpp"

#include <iostream>

namespace Universe
{
    // Debug callback function
    void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                GLsizei length, const GLchar* message, const void* userParam) {
        std::cerr << "[OpenGL Debug Message] " << message << std::endl;

        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                std::cerr << "Severity: HIGH" << std::endl;
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                std::cerr << "Severity: MEDIUM" << std::endl;
                break;
            case GL_DEBUG_SEVERITY_LOW:
                std::cerr << "Severity: LOW" << std::endl;
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                std::cerr << "Severity: NOTIFICATION" << std::endl;
                break;
        }
    }

    Application::Application()
    {
        if (!glfwInit()) {
            UE_CORE_INFO("Failed to initialize GLFW");
            const char* description;
            glfwGetError(&description);
            UE_CORE_ASSERT(false, description);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

        m_Window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
        if (!m_Window) {
            UE_CORE_ASSERT(false, "Failed to create GLFW window");
            glfwTerminate();
        }
        
        glfwMakeContextCurrent(m_Window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            UE_CORE_ASSERT(false, "Failed to initialize GLAD");
        }
        // Check if debug context is active
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            std::cout << "Debug context enabled" << std::endl;
        }
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Optional: makes errors appear immediately
        glDebugMessageCallback(DebugCallback, nullptr);
        if (glfwGetCurrentContext() == nullptr) {
            UE_CORE_ASSERT(false, "Failed to set OpenGL context");
        }
        UE_CORE_TRACE("OpenGL context set");
        const unsigned char* version = glGetString(GL_VERSION);
        std::cout << version << std::endl;
    }

    Application::~Application()
    {    
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            // Run the application
            UE_CORE_TRACE("Running the application");

            glClear(GL_COLOR_BUFFER_BIT);

            glEnable(GL_INVALID_ENUM);

            // Poll events
            glfwPollEvents();

            // Swap buffers
            glfwSwapBuffers(m_Window);

            // Exit the application
            if (!m_IsRunning)
            {
                UE_CORE_TRACE("Exiting the application");
            }
        }
        
    }
}