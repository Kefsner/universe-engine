#pragma once

#include "engine/window/window.hpp"
#include "engine/events/event.hpp"
#include "engine/events/application_event.hpp"
#include "engine/layers/layer_stack.hpp"

namespace Universe {

    class Application {
    public:
        Application();
        
        void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
        Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }

    private:
        std::unique_ptr<Window> m_Window; ///< The main application window.
        bool m_IsRunning = true; ///< Flag indicating whether the application is running.
        LayerStack m_LayerStack; ///< The stack of layers managed by the application.
        static Application* s_Instance; ///< The singleton instance of the application.
        float m_LastFrameTime = 0.0f;

        bool OnWindowClose(WindowCloseEvent& e);
    };

    Application* CreateApplication();
}
