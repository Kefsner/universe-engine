#pragma once
#include "engine/core/window.hpp"

namespace Universe {

	class Application
	{
	public:
		Application();
		void Run();

	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};

	Application* CreateApplication();
}