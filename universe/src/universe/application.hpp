#pragma once

#include <GLFW/glfw3.h>

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
        GLFWwindow* m_Window;
    };

    Application* Create();
}