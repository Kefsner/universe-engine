#pragma once

#include "universe/base/base.hpp"
#include "universe/window/window.hpp"

namespace Universe
{
    class Application
    {
    public:      
        Application();
        ~Application();

        void Run();

    private:
        bool m_IsRunning = true;
        Scope<Window> m_Window;
    };

    Application* Create();
}