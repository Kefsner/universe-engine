#pragma once
#include "engine/window/window.hpp"
#include "engine/renderer/graphics_context.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Universe {

    class GLFWWindowWrapper : public Window
    {
    public:
        GLFWWindowWrapper(const WindowProps& props);
        ~GLFWWindowWrapper();

        void OnUpdate() override;
        void SetEventCallback(const std::function<void(Event&)>& callback) override { m_Data.EventCallback = callback; }
        void* GetNativeWindow() const override { return m_Window; }

    private:
        void SetCallbacks(); ///< Sets up the GLFW event callbacks for the window.

        GLFWwindow* m_Window; ///< Pointer to the GLFW window.
        GraphicsContext* m_Context; ///< Pointer to the rendering context.

        struct WindowData {
            std::string Title; ///< The title of the window.
            unsigned int Width; ///< The width of the window in pixels.
            unsigned int Height; ///< The height of the window in pixels.
            std::function<void(Event&)> EventCallback; ///< The callback function for handling events.
        };
        WindowData m_Data; ///< Metadata about the window.
    };
}
