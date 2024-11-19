#pragma once
#include "engine/window/window.hpp"
#include "engine/events/event.hpp"
#include "engine/events/application_event.hpp"
#include "engine/layers/layer_stack.hpp"

namespace Universe {

	class Application
	{
	public:
		Application();

		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);

		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }

	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;

		bool OnWindowClose(WindowCloseEvent& e);
	};

	Application* CreateApplication();
}