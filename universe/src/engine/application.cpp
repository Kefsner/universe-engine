#include "engine/application.hpp"

namespace Universe {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			m_Window->OnUpdate();
		}
	}	
}