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
        EventType GetType() { return EventType::KeyPress; }

    private:
        double m_XPos, m_YPos;
    };

    // class MousePressEvent : public Event
    // {
    // public:
    //     MousePressEvent();
    //     ~MousePressEvent() override = default;

    //     std::string ToString() override;
    //     EventType GetType() { return EventType::KeyPress; }
    // };
}