#pragma once

#include <GLFW/glfw3.h>

#include "universe/core/core.hpp"
#include "universe/window/window.hpp"
#include "universe/renderer/graphics_context.hpp"

namespace Universe {

    class GLFWWindowWrapper : public Window
    {
    public:
        // Constructor and Destructor
        GLFWWindowWrapper(const WindowProps& props);
        ~GLFWWindowWrapper();

        // Virtual functions
        void OnUpdate() override;
        void SetEventCallback(const std::function<void(Event&)>& callback) override { m_WindowData.EventCallback = callback; }
        void* GetNativeWindow() const override { return m_Window; }

        void SetVSync(bool enabled) override { enabled ? glfwSwapInterval(1) : glfwSwapInterval(0); m_WindowData.VSync = enabled; }
        bool IsVSync() const override { return m_WindowData.VSync; }
        float GetTime() const override { return (float)glfwGetTime(); }

    private:
        struct WindowData
        {
            // From WindowProps
            std::string Title;          // Window title
            unsigned int Width, Height; // Window dimensions
            bool VSync;                 // FPS cap based on monitor refresh rate

            // Not from WindowProps
            std::function<void(Event&)> EventCallback; // Event callback function
        };

        // Window data
        WindowData m_WindowData;    // The window data. Initialized in the constructor from the WindowProps.
        GLFWwindow* m_Window;       // Pointer to the GLFW window from glfwCreateWindow.
        Ref<GraphicsContext> m_Context; // Pointer to the OpenGL context.

        // Private functions
        void SetCallbacks();        // Set the GLFW callbacks.

    };
}
