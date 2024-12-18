#include "pch.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "universe/base/base.hpp"
#include "universe/application.hpp"
#include "universe/base/logger.hpp"
#include "universe/base/assert.hpp"
#include "universe/events/application_events.hpp"
#include "universe/window/window.hpp"


namespace Universe
{
    Application::Application()
    {
        m_Window = Window::Create();

        m_Window->SetEventCallback(UE_BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application()
    {    
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(UE_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(Application::OnWindowResize));
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_IsRunning = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        // Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        return false;
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            if (!m_Minimized)
            {
                // for (Layer* layer : m_LayerStack)
                //     layer->OnUpdate();

                m_Window->OnUpdate();
            }
        }
        
    }
}