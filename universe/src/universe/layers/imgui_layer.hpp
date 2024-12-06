#pragma once

#include "universe/layers/layer.hpp"

namespace Universe {

    class ImGuiLayer : public Layer
    {
    public:
        // Constructor and Destructor
        ImGuiLayer() = default;
        ~ImGuiLayer() = default;

        // Virtual functions
        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        // ImGui functions
        void Begin();
        void End();
        void ShowPerformanceMetrics();
    };
}