#pragma once

#include <sstream>

#include "universe/events/event.hpp"

namespace Universe {

    class MouseMovedEvent : public Event
    {
    public:
        // Constructor and Destructor
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
        ~MouseMovedEvent() = default;

        // Virtual functions
        EventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "MouseMoved"; }
        int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        // Static functions
        static EventType GetStaticType() { return EventType::MouseMoved; }

        // Getters
        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

    private:
        float m_MouseX, m_MouseY; // New mouse position
    };

    class MouseScrolledEvent : public Event
    {
    public:
        // Constructor and Destructor
        MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}
        ~MouseScrolledEvent() = default;

        // Virtual functions
        EventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "MouseScrolled"; }
        int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }

        // Static functions
        static EventType GetStaticType() { return EventType::MouseScrolled; }

        // Getters
        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

    private:
        float m_XOffset, m_YOffset; // Scroll offset
    };

    class MouseButtonEvent : public Event
    {
    protected:
        // Protected constructor
        MouseButtonEvent(int button) : m_Button(button) {}
        int m_Button; // Button code of the mouse button event

    public:
        // Destructor
        virtual ~MouseButtonEvent() = default;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        // Constructor and Destructor
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
        ~MouseButtonPressedEvent() = default;
    
        // Virtual functions
        EventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "MouseButtonPressed"; }
        int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        // Static functions
        static EventType GetStaticType() { return EventType::MouseButtonPressed; }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        // Constructor and Destructor
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}
        ~MouseButtonReleasedEvent() = default;

        // Virtual functions
        EventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "MouseButtonReleased"; }
        int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        // Static functions
        static EventType GetStaticType() { return EventType::MouseButtonReleased; }
    };

}
