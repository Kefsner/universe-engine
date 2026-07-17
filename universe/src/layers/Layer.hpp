#pragma once

namespace Universe
{
    class Layer
    {
    public:
        Layer() {}
        virtual ~Layer() = default;

        virtual void OnUpdate() = 0;
    };
}