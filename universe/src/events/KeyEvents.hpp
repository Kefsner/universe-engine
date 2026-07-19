#include "events/Event.hpp"

#include <string>

namespace Universe
{
    enum KeyCode
    {
        NONE = 0
    };

    class KeyPressEvent : public Event
    {
    public:
        KeyPressEvent(int key);
        ~KeyPressEvent() override = default;

        std::string ToString() override;
        EventType GetType() { return EventType::KeyPress; }

    private:
        int m_Key;
    };

    class KeyReleaseEvent : public Event
    {
    public:
        KeyReleaseEvent(int key);
        ~KeyReleaseEvent() override = default;

        std::string ToString() override;
        EventType GetType() { return EventType::KeyRelease; }

    private:
        int m_Key;
    };

    class KeyRepeatEvent : public Event
    {
    public:
        KeyRepeatEvent(int key);
        ~KeyRepeatEvent() override = default;

        std::string ToString() override;
        EventType GetType() { return EventType::KeyRepeat; }

    private:
        int m_Key;
    };
}