#pragma once

#include "engine/layers/layer.hpp"
#include "engine/events/event.hpp"

namespace Universe {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;
    };
}