#include "pch.hpp"
#include "engine/core.hpp"
#include "engine/application.hpp"
#include "engine/timestep.hpp"
#include "engine/logger/logger.hpp"
#include "engine/renderer/renderer.hpp"

namespace Universe {

    Application* Application::s_Instance = nullptr;

    Application::Application()
	{
        UE_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(UE_BIND_EVENT_FN(Application::OnEvent));
        
        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }


    void Application::Run() {
        while (m_IsRunning) {
            float time = m_Window->GetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized) {
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate(timestep);
            }
            
            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event& e) {

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(UE_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(UE_BIND_EVENT_FN(Application::OnWindowResize));
        
        // Propagate the event through the LayerStack in reverse order
        // Stops when a layer marks the event as handled
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            --it;
            Layer* layer = *it;
            layer->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_IsRunning = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e) {
        if (e.GetWidth() == 0 || e.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }
        m_Minimized = false;

        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        
        return false;
    }

}
