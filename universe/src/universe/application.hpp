#pragma once

#include <memory> // std::unique_ptr

#include "universe/events/event.hpp"
#include "universe/window/window.hpp"
#include "universe/layers/layer_stack.hpp"          // Also includes Layer.hpp
#include "universe/layers/imgui_layer.hpp"          // Also includes Layer.hpp
#include "universe/events/application_event.hpp"    // Also includes Event.hpp


namespace Universe {

    class Application
    {
    public:
        // Constructor
        Application();
        
        // Main loop
        void Run();

        // Event handling
		void OnEvent(Event& e);

        // Layer Management
		void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        // Getters
        Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }

    private:
        // Core states
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_LayerStack;

        // Application states
        static Application* s_Instance;
        bool m_IsRunning = true;
        bool m_Minimized = false;
        float m_LastFrameTime = 0.0f;

        // Event Callbacks
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}
