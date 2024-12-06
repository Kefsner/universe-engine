#pragma once

#include <functional>
#include <string>

#include "universe/core/core.hpp"
#include "universe/events/event.hpp"

namespace Universe {

    struct WindowProps
    {
        WindowProps(
            const std::string& title = "Universe Engine",
            unsigned int width = 1280,
            unsigned int height = 720,
            bool vsync = true
        ) : Title(title), Width(width), Height(height), VSync(vsync) {}
        ~WindowProps() = default;

        std::string Title;              // Window title
        unsigned int Width, Height;     // Window dimensions
        bool VSync;                     // FPS cap based on monitor refresh rate
    };

    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void OnUpdate() = 0;
        virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;
        virtual void* GetNativeWindow() const = 0;

        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;
        virtual float GetTime() const = 0;

        static Scope<Window> Create(const WindowProps& props = WindowProps());
    };
}