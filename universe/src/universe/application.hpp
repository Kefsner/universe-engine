#pragma once

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
    };

    Application* Create();
}