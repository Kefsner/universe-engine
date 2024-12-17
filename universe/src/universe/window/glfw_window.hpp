#pragma once

#include <GLFW/glfw3.h>

#include "universe/base/base.hpp"
#include "universe/window/window.hpp"
#include "universe/renderer/graphics_context.hpp"

namespace Universe
{
    class GLFWWindowWrapper : public Window
    {
    public:
        GLFWWindowWrapper(const WindowProps& props);
        ~GLFWWindowWrapper();

        virtual void OnUpdate() override;
        virtual float GetWidth() const override { return m_Data.Width; }
        virtual float GetHeight() const override { return m_Data.Height; }
        virtual void SetVSync(bool enabled) override { m_Data.VSync = enabled; }
        virtual bool IsVSync() const override { return m_Data.VSync; }

    private:
        struct WindowData
        {
            std::string Title;
            float Width, Height;
            bool VSync;
        };
        WindowData m_Data;
        GLFWwindow* m_Window;
        Ref<GraphicsContext> m_Context;
    };
}