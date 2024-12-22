#pragma once

#include <GLFW/glfw3.h>

#include "universe/base/base.hpp"
#include "universe/window/window.hpp"
#include "universe/renderer/graphics_context.hpp"

namespace Universe
{
	using EventCallbackFn = std::function<void(Event&)>;

    class GLFWWindowWrapper : public Window
    {
    public:
        GLFWWindowWrapper(const WindowProps& props);
        ~GLFWWindowWrapper();

        virtual void OnUpdate() override;

        virtual float GetWidth() const override { return m_Data.Width; }
        virtual float GetHeight() const override { return m_Data.Height; }
        virtual void SetWidth(float width) { m_Data.Width = width; }
        virtual void SetHeight(float height) { m_Data.Height = height; }

        virtual bool IsVSync() const override { return m_Data.VSync; }
        virtual void SetVSync(bool enabled) override;

        virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        virtual void* GetNativeWindow() const override { return m_Window; }

        virtual void UpdateViewport(int width, int height);

        void SetCallbacks();

    private:
        struct WindowData
        {
            std::string Title;
            float Width, Height;
            bool VSync;
            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
        GLFWwindow* m_Window;
        Ref<GraphicsContext> m_Context;
    };
}