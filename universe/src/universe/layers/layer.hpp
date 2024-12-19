#pragma once

#include "universe/base/timestep.hpp"
#include "universe/events/events.hpp"

namespace Universe
{
    class Layer
    {
    public:
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnEvent(Event& event) {}
    };
}