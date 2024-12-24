#pragma once

#include "universe/renderer/render_command.hpp"
#include "universe/renderer/renderer2D.hpp"

namespace Universe
{
    class Renderer
    {
    public:
        static void Init()
        {
            RenderCommand::Init();
            Renderer2D::Init();
        }
        static void Shutdown()
        {
            RenderCommand::Shutdown();
            Renderer2D::Shutdown();
        }
    };
}