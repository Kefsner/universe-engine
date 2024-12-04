#pragma once
#include "engine/layers/layer.hpp"

namespace Universe {

    class ImGuiLayer : public Layer {
    public:
        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;
        void Begin();
        void End();

        void ShowPerformanceMetrics(bool* p_open);
        
    private:
        bool m_BlockEvents = true;
    };
}