#pragma once

#include "universe/base/base.hpp"
#include "universe/window/window.hpp"
#include "universe/events/events.hpp"
#include "universe/events/application_events.hpp"

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

    private:
        bool m_IsRunning = true;
        bool m_Minimized = false;
        Scope<Window> m_Window;
    };

    Application* Create();
}