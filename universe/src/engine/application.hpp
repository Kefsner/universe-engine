#pragma once
#include "engine/window/window.hpp"
#include "engine/events/event.hpp"
#include "engine/events/application_event.hpp"
#include "engine/layers/layer_stack.hpp"
#include "engine/layers/imgui_layer.hpp"

namespace Universe {

    class Application {
    public:
        Application();
        
        void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }

    private:
        std::unique_ptr<Window> m_Window;
        static Application* s_Instance;
        bool m_IsRunning = true;
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;
        float m_LastFrameTime = 0.0f;

        bool OnWindowClose(WindowCloseEvent& e);
    };

    Application* CreateApplication();
}
