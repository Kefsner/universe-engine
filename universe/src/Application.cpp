#include "Application.hpp"

#include "core/Logger.hpp"

#include "renderer/Renderer.hpp"

namespace Universe
{
    Application::Application()
    {
        WindowProps windowProps{
            .Width = 1920,
            .Height = 1080,
            .Title = "Hello, Universe!",
            .Debug = false
        };
    #ifdef UNIVERSE_DEBUG
        windowProps.Debug = true;
    #endif
        m_Window = std::make_unique<Window>(windowProps);
    
        Renderer::Init();

        m_IsRunning = true;
    }

    void Application::Run()
    {
        while (!m_Window->ShouldClose())
        {
            m_Window->Update();

            for (auto it = m_LayerStack.Begin(); it != m_LayerStack.End(); it++)
            {
                std::shared_ptr<Layer> layer = *it;
                layer->OnUpdate();
            }
        }
    }

    void Application::AddLayer(std::shared_ptr<Layer> layer)
    {
        m_LayerStack.AddLayer(layer);
    }
}
