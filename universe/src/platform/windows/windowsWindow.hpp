#pragma once
#include "engine/core/window.hpp"
#include <GLFW/glfw3.h>

namespace Universe {

    class WindowsWindow : public Window {
        public:
            WindowsWindow(const WindowProps& props);
            ~WindowsWindow();
            void OnUpdate() override;

        private:
            GLFWwindow* m_Window;

            struct WindowData {
                std::string Title;
                unsigned int Width;
                unsigned int Height;
            };
            WindowData m_Data;
    };
}

