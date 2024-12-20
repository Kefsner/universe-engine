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
        virtual std::string ToString() const override { return "WindowCloseEvent"; }
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(float width, float height)
            : m_Width(width), m_Height(height) {}

        static EventType GetStaticType() { return EventType::WindowResize; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        float GetWidth() const { return m_Width; }
        float GetHeight() const { return m_Height; }

    private:
        float m_Width, m_Height;
    };
}