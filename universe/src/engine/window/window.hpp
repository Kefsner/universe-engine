#pragma once
#include "pch.hpp"
#include "engine/events/event.hpp"

namespace Universe {

    struct WindowProps {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(
            const std::string& title = "Universe Engine",
            unsigned int width = 1280,
            unsigned int height = 720
        ) : Title(title), Width(width), Height(height) {}
    };

    class Window {
        public:
            virtual ~Window() = default;

            virtual void OnUpdate() = 0;
            virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;

            static Window* Create(const WindowProps& props = WindowProps());
    };
}