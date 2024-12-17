#include "pch.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "universe/application.hpp"
#include "universe/base/logger.hpp"
#include "universe/base/assert.hpp"
#include "universe/window/window.hpp"

#include <iostream>

namespace Universe
{
    Application::Application()
    {
        m_Window = Window::Create();
    }

    Application::~Application()
    {    
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            m_Window->OnUpdate();
            
            // Set the clear color
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            // Poll events
            glfwPollEvents();

        }
        
    }
}