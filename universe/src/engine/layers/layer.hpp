#pragma once
#include "engine/timestep.hpp"
#include "engine/events/event.hpp"

namespace Universe {
    
    class Layer
    {
    public:
        virtual ~Layer() = default;
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnEvent(Event& event) {}
        virtual void OnImGuiRender() {}
    };
}
