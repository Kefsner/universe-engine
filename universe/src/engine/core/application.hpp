#pragma once

namespace Universe {

	class Application
	{
	public:
		Application();
		void Run();

	private:
		static Application* s_Instance;
		bool m_IsRunning = true;
	};

	Application* CreateApplication();
}