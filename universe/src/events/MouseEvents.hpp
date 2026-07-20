#pragma once

#include "events/Event.hpp"

namespace Universe
{
    class MouseMoveEvent : public Event
    {
    public:
        MouseMoveEvent(double xpos, double ypos);
        ~MouseMoveEvent() override = default;

        std::string ToString() override;
        EventType GetType() { return EventType::MouseMove; }

    private:
        double m_XPos, m_YPos;
    };

    class MouseButtonEvent : public Event
    {
    public:
        MouseButtonEvent(int key);
        ~MouseButtonEvent() override = default;

        std::string ToString() override;
        EventType GetType() { return EventType::MouseButton; }

    private:
        int m_Key;
    };


    class MouseScrollEvent : public Event
    {
    public:
        MouseScrollEvent(double offset);
        ~MouseScrollEvent() override = default;

        std::string ToString() override;
        EventType GetType() { return EventType::MouseScroll; }

    private:
        int m_Offset;
    };
}