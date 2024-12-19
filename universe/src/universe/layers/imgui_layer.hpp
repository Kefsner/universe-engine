#pragma once

#include "universe/layers/layer.hpp"

namespace Universe
{
    class ImGuiLayer : public Layer
    {
    public:
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Timestep ts) override;

    private:
        bool m_ShowDemoWindow = true;
    };
}