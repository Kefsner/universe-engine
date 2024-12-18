#pragma once

#include "universe/events/events.hpp"
#include "universe/events/key_codes.hpp"

namespace Universe
{
    class KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }

    protected:
        KeyEvent(int keycode)
            : m_KeyCode(keycode) {}

        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(KeyCode keycode, uint8_t repeatCount)
            : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        static EventType GetStaticType() { return EventType::KeyPressed; }
        virtual EventType GetEventType() const override { return GetStaticType(); }

        uint8_t GetRepeatCount() const { return m_RepeatCount; }

    private:
        uint8_t m_RepeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}

        static EventType GetStaticType() { return EventType::KeyReleased; }
        virtual EventType GetEventType() const override { return GetStaticType(); }
    };
}