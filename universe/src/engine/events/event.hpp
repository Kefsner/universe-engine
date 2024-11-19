#pragma once
#include "engine/utils.hpp"
#include "engine/logger/logger.hpp"

namespace Universe {
    
    enum class EventType
    {
        None = 0,
        // Application events
        WindowClose,
        WindowResize,
        // Keyboard events
        KeyPressed,
        KeyReleased,
        // Mouse events
        MouseMoved,
        MouseScrolled,
        MouseButtonPressed,
        MouseButtonReleased
    };

    class Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event) {}

        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            m_Event.Handled = func(static_cast<T&>(m_Event));
            return true;
        }

    private:
        Event& m_Event;
    };
}