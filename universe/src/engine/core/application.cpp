#include "engine/core/application.hpp"
#include "engine/core/logger/logger.hpp"

namespace Universe {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			UE_CORE_INFO("Running Universe!");
		}
	}	
}