#pragma once

#include "core/Window.hpp"
#include "events/Event.hpp"
#include "layers/Layer.hpp"
#include "layers/LayerStack.hpp"

#include <memory>

namespace Universe
{
    // Application* Application::s_Instance = nullptr;

    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        static Application* Get() { return s_Instance; }
        Window& GetWindow() { return *m_Window; }

        void Run();

        void OnEvent(Event& event);

        void AddLayer(std::shared_ptr<Layer> layer);

        static Application* CreateApplication();

    private:
        static Application* s_Instance;

        bool m_IsRunning;
        LayerStack m_LayerStack;
        std::unique_ptr<Window> m_Window;
    };
}
