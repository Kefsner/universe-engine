#pragma once

#include "universe/events/events.hpp"

namespace Universe
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        static EventType GetStaticType() { return EventType::WindowClose; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(float width, float height)
            : m_Width(width), m_Height(height) {}

        static EventType GetStaticType() { return EventType::WindowResize; }
        virtual EventType GetEventType() const override { return GetStaticType(); }

        float GetWidth() const { return m_Width; }
        float GetHeight() const { return m_Height; }

    private:
        float m_Width, m_Height;
    };
}