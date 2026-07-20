#include "Application.hpp"

#include "core/Logger.hpp"
#include "events/Event.hpp"
#include "events/WindowEvents.hpp"

#include "renderer/Renderer.hpp"

namespace Universe
{
    Application* Application::s_Instance = nullptr;
    
    Application::Application()
    {
        WindowProps windowProps{
            .Width = 1920,
            .Height = 1080,
            .Title = "Hello, Universe!",
            .Debug = false
        };
    #ifdef UNIVERSE_DEBUG
        windowProps.Debug = true;
    #endif
        m_Window = std::make_unique<Window>(windowProps);
        m_Window->SetEventCallbackFn(
            [this](Event& event)
            {
                OnEvent(event);
            }
        );
    
        Renderer::Init();

        m_IsRunning = true;
        Application::s_Instance = this;
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            for (auto it = m_LayerStack.Begin(); it != m_LayerStack.End(); it++)
            {
                std::shared_ptr<Layer> layer = *it;
                layer->OnUpdate();
            }

            m_Window->Update();
        }
    }

    void Application::OnEvent(Event& event)
    {
        UE_CORE_INFO("Event triggered: {}", event.ToString());

        if (event.GetType() == EventType::WindowResize)
        {
            m_Window->OnResize(
                static_cast<WindowResizeEvent&>(event).GetWidth(),
                static_cast<WindowResizeEvent&>(event).GetHeight()
            );

            event.SetHandled();
            return;
        }

        if (event.GetType() == EventType::WindowClose)
        {
            m_IsRunning = false;

            event.SetHandled();
            return;
        }
    }

    void Application::AddLayer(std::shared_ptr<Layer> layer)
    {
        m_LayerStack.AddLayer(layer);
    }
}
