#include "engine/application.hpp"
#include "engine/logger/logger.hpp"
#include "engine/renderer/renderer.hpp"

namespace Universe {

    // Initialize the singleton instance pointer
    Application* Application::s_Instance = nullptr;

    Application::Application()
	{
        UE_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		Renderer::Init(); // Do nothing for now
    }

	Application::~Application()
	{
		Renderer::Shutdown(); // Do nothing for now
	}

    void Application::Run() {
        while (m_IsRunning) {
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();
            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* layer) {
        // Add the layer to the stack and call its OnAttach method for initialization
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e) {
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

}
