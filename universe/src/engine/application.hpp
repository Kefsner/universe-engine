#pragma once
#include "engine/window/window.hpp"
#include "engine/events/event.hpp"
#include "engine/events/application_event.hpp"

namespace Universe {

	class Application
	{
	public:
		Application();

		void Run();

		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};

	Application* CreateApplication();
}