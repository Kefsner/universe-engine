#pragma once

namespace Universe
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        void Run();

        static Application* CreateApplication();

    private:
        bool m_IsRunning;
    };
}
