#pragma once

#include <string>
#include <functional>

#include "universe/base/base.hpp"
#include "universe/events/events.hpp"

namespace Universe
{
    struct WindowProps
    {
        std::string Title;
        float Width;
        float Height;
        bool VSync;

        WindowProps(const std::string& title = "Universe Engine",
                    float width = 1280,
                    float height = 720,
                    bool vsync = true)
            : Title(title), Width(width), Height(height), VSync(vsync)
        {
        }
    };

    class Window
    {
    public:
        virtual ~Window() = default;
        
        virtual void OnUpdate() = 0;

        virtual float GetWidth() const = 0;
        virtual float GetHeight() const = 0;
        virtual void SetWidth(float width) = 0;
        virtual void SetHeight(float height) = 0;

        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;
        virtual void* GetNativeWindow() const = 0;

        virtual void UpdateViewport(int width, int height) = 0;

        static Scope<Window> Create(const WindowProps& props = WindowProps());
    };
}