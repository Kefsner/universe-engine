#pragma once
#include "engine/window/window.hpp"
#include "engine/renderer/graphics_context.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Universe {

    class GLFWWindowWrapper : public Window {
        public:
            GLFWWindowWrapper(const WindowProps& props);
            ~GLFWWindowWrapper();

            void OnUpdate() override;
            void SetEventCallback(const std::function<void(Event&)>& callback) override { m_Data.EventCallback = callback; }
            void* GetNativeWindow() const override { return m_Window; }

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

