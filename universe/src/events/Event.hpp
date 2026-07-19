#pragma once

#include <string>

namespace Universe
{
    enum class EventType
    {
        None = 0,
        KeyPress, KeyRelease, KeyRepeat,

        MouseMove, MousePress,

        WindowResize
    };

    class Event
    {
    public:
        virtual ~Event() = default;

        virtual std::string ToString() = 0;
        virtual EventType GetType() = 0;

        void SetHandled() { m_IsHandled = true; }

    private:
        bool m_IsHandled = false;
    };
}