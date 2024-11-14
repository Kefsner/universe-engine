#pragma once
#include "engine/window/window.hpp"
#include "engine/renderer/graphics_context.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Universe {

    class UEGLFWWindow : public Window {
        public:
            UEGLFWWindow(const WindowProps& props);
            ~UEGLFWWindow();

            void OnUpdate() override;

        private:
            GLFWwindow* m_Window;
            GraphicsContext* m_Context;

            struct WindowData {
                std::string Title;
                unsigned int Width;
                unsigned int Height;
            };
            WindowData m_Data;
    };
}

