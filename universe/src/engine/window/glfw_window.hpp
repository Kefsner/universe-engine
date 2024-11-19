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
            void SetEventCallback(const std::function<void(Event&)>& callback) override 
            {
                m_Data.EventCallback = callback;
                UE_CORE_INFO("Event callback set!");
            }

        private:
            GLFWwindow* m_Window;
            GraphicsContext* m_Context;

            struct WindowData {
                std::string Title;
                unsigned int Width;
                unsigned int Height;
                
                std::function<void(Event&)> EventCallback;
            };
            WindowData m_Data;
    };
}

