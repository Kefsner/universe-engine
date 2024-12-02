#pragma once
#include "engine/layers/layer.hpp"

namespace Universe {

    class ImGuiLayer : public Layer {
    public:
        void OnAttach() override;
        void OnDetach() override;
        void OnEvent(Event& event) override;
        void Begin();
        void End();

    private:
        bool m_BlockEvents = true;
    };
}