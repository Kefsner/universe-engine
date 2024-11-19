#include "engine/application.hpp"
#include "engine/logger/logger.hpp"

namespace Universe {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		// EventDispatcher dispatcher(e);
		// dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		UE_CORE_TRACE("{0}", e.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}
}