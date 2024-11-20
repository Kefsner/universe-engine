#pragma once

#include "engine/events/event.hpp"

namespace Universe {
    
    class Layer
    {
    public:
        Layer() = default;
        virtual ~Layer() = default;
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}
    };
}
