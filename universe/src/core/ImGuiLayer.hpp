#pragma once

#include "core/Window.hpp"

namespace Universe
{
    class ImGuiLayer
    {
    public:
        ImGuiLayer(const Window& window);
        ~ImGuiLayer() = default;

        void BeginFrame();
        void Draw();
        void EndFrame();
    };
}