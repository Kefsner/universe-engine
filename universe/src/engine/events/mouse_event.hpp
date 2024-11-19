#pragma once

#include <sstream>
#include "engine/events/event.hpp"

namespace Universe {

    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {}

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        EventType GetEventType() const override { return EventType::MouseMoved; }
        const char* GetName() const override { return "MouseMoved"; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

    private:
        float m_MouseX, m_MouseY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        EventType GetEventType() const override { return EventType::MouseScrolled; }
        const char* GetName() const override { return "MouseScrolled"; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }

    private:
        float m_XOffset, m_YOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        int GetMouseButton() const { return m_Button; }

    protected:
        MouseButtonEvent(int button)
            : m_Button(button) {}

        int m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}

        EventType GetEventType() const override { return EventType::MouseButtonPressed; }
        const char* GetName() const override { return "MouseButtonPressed"; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}

        EventType GetEventType() const override { return EventType::MouseButtonReleased; }
        const char* GetName() const override { return "MouseButtonReleased"; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }
    };
}