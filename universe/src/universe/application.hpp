#pragma once

#include "universe/base/base.hpp"
#include "universe/window/window.hpp"
#include "universe/events/events.hpp"
#include "universe/events/application_events.hpp"
#include "universe/layers/layer_stack.hpp"

namespace Universe
{
    class Application
    {
    public:      
        Application();
        ~Application();

        void OnEvent(Event& e);
        void Run();

        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

        static Application& Get() { return *s_Instance; }
        Window& GetWindow() { return *m_Window; }

        void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }
        void PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); }

    private:
        static Application* s_Instance;
        bool m_IsRunning = true;
        bool m_Minimized = false;
        float m_LastFrameTime = 0.0f;
        LayerStack m_LayerStack;
        Scope<Window> m_Window;
    };

    Application* Create();
}