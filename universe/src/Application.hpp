#pragma once

#include "core/Window.hpp"
#include "layers/Layer.hpp"
#include "layers/LayerStack.hpp"

#include <memory>

namespace Universe
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        void Run();

        void AddLayer(std::shared_ptr<Layer> layer);

        static Application* CreateApplication();

    private:
        bool m_IsRunning;
        LayerStack m_LayerStack;
        std::unique_ptr<Window> m_Window;
    };
}
