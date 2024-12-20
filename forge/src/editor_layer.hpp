#pragma once

#include "universe.hpp"

namespace Universe
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer() = default;
        ~EditorLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Timestep ts) override;
        virtual void OnEvent(Event& event) override;
    };
}