#pragma once

#include <string>

#include "universe/base/base.hpp"
#include "universe/base/logger.hpp"


namespace Universe
{
    enum class EventType
    {
        None = 0,
        // Application events
        WindowClose, WindowResize,
        // Input events
        KeyPressed, KeyReleased,
        // Mouse events
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled 
    };
    
    class Event
    {
    public:
        virtual ~Event() = default;
        virtual EventType GetEventType() const = 0;
        bool m_Handled = false;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event) {}

        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_Handled = func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };
}