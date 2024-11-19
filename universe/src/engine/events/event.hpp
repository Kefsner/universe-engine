#pragma once
#include "engine/utils.hpp"
#include "engine/logger/logger.hpp"

namespace Universe {

    enum class EventType {
        None = 0,
        WindowClose
    };

    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0)
    };

    class Event
    {
    public:
        virtual ~Event() = default;
        bool Handled = false;
        virtual EventType GetEventType() const = 0;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event) {}
        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            UE_INFO("Event dispatched!");
            // if (m_Event.GetEventType() == T::GetStaticType())
            // {
            //     m_Event.Handled = func(static_cast<T&>(m_Event));
            //     return true;
            // }
            // return false;
            m_Event.Handled = func(static_cast<T&>(m_Event));
            return true; // Remove the if statement in order to see when this could go wrong
        }
    private:
        Event& m_Event;
    };
}