#pragma once
#include "engine/window/window.hpp"

namespace Universe {

	class Application
	{
	public:
		Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};

	Application* CreateApplication();
}