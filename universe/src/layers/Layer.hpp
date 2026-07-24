#pragma once

#include "core/Timestep.hpp"

namespace Universe
{
    class Layer
    {
    public:
        Layer() {}
        virtual ~Layer() = default;

        virtual void OnUpdate(Timestep ts) = 0;
    };
}