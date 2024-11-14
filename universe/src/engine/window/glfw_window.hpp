#pragma once
#include "engine/window/window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Universe {

    class GLFWWindow : public Window {
        public:
            GLFWWindow(const WindowProps& props);
            ~GLFWWindow();

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

