#pragma once
#include "pch.hpp"
#include "engine/events/event.hpp"

namespace Universe {

    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;
        bool VSync;

        WindowProps(
            const std::string& title = "Universe Engine",
            unsigned int width = 1280,
            unsigned int height = 720,
            bool vsync = true
        ) : Title(title), Width(width), Height(height) {}
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

        static Window* Create(const WindowProps& props = WindowProps());
    };
}