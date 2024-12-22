#include "pch.hpp"

#include "universe/application.hpp"
#include "universe/base/logger.hpp"
#include "universe/base/assert.hpp"


namespace Universe
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        UE_CORE_INFO("Creating Application");
        UE_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

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

        for (Layer* layer : m_LayerStack | std::views::reverse)
        {
            layer->OnEvent(e);
            if (e.m_Handled)
                break;
        }
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
        m_Window->UpdateViewport(e.GetWidth(), e.GetHeight());

        return false; // Don't consume the event and allow propagation to other layers
    }

    void Application::Run()
    {
        float ts = 0.0f;

        while (m_IsRunning)
        {
            float time = m_Window->GetTime();
            ts = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized)
            {
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate(ts);

                m_Window->OnUpdate();
            }
        }
    }
}