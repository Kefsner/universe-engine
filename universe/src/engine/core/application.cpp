#include "engine/core/application.hpp"
#include "engine/core/logger/logger.hpp"

#include <thread>
#include <chrono>

namespace Universe {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		UE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

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