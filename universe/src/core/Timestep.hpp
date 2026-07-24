#pragma once

namespace Universe
{
    class Timestep
    {
    public:
        Timestep(float time = 0.0f);
        ~Timestep() = default;

        operator float() const { return m_Time; }

    private:
        float m_Time;
    };
}
