#pragma once

#include <sstream>

#include "universe/events/event.hpp"

namespace Universe {

    class KeyEvent : public Event
    {
    protected:
        // Protected constructor
        KeyEvent(int keycode) : m_KeyCode(keycode) {}
        int m_KeyCode; // Key code of the key event

    public:
        // Destructor
        virtual ~KeyEvent() = default;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        // Constructor and Destructor
        KeyPressedEvent(int keycode, bool repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
        ~KeyPressedEvent() = default;

        // Virtual functions
        EventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "KeyPressed"; }
        int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (Repeat: " << (m_RepeatCount ? "true" : "false") << ")";
            return ss.str();
        }

        // Static functions
        static EventType GetStaticType() { return EventType::KeyPressed; }

    private:
        bool m_RepeatCount; // Whether the key event is a repeat
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        // Constructor and Destructor
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
        ~KeyReleasedEvent() = default;

        // Virtual functions
        EventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "KeyReleased"; }
        int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        // Static functions
        static EventType GetStaticType() { return EventType::KeyReleased; }
    };
}
