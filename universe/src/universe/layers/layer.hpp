#pragma once

#include "universe/core/timestep.hpp"
#include "universe/events/event.hpp"

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
