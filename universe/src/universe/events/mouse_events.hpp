#pragma once

#include "universe/base/base.hpp"
#include "universe/events/events.hpp"
#include "universe/inputs/mouse_codes.hpp"

namespace Universe
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(const float x, const float y)
            : m_MousePosX(x), m_MousePosY(y) {}

        static EventType GetStaticType() { return EventType::MouseMoved; }
        virtual EventType GetEventType() const override { return GetStaticType(); }

        float GetMousePosX() const { return m_MousePosX; }
        float GetMousePosY() const { return m_MousePosY; }
        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MousePosX << ", " << m_MousePosY;
            return ss.str();
        }

    private:
        float m_MousePosX, m_MousePosY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset)
            : m_MouseXOffset(xOffset), m_MouseYOffset(yOffset) {}

        static EventType GetStaticType() { return EventType::MouseScrolled; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_MouseXOffset << ", " << m_MouseYOffset;
            return ss.str();
        }

        float GetMouseXOffset() const { return m_MouseXOffset; }
        float GetMouseYOffset() const { return m_MouseYOffset; }

    private:
        float m_MouseXOffset, m_MouseYOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        MouseCode GetMouseButton() const { return m_Button; }
    protected:
        MouseButtonEvent(const int button)
            : m_Button(button) {}
        MouseCode m_Button;
    };


    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(const int button)
            : MouseButtonEvent(button) {}

        static EventType GetStaticType() { return EventType::MouseButtonPressed; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(const int button)
            : MouseButtonEvent(button) {}
        
        static EventType GetStaticType() { return EventType::MouseButtonReleased; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }
    };
}