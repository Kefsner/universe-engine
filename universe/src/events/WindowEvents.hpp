#include "events/Event.hpp"

namespace Universe
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int width, int height);
        ~WindowResizeEvent() override = default;
        
        std::string ToString() override;

        EventType GetType() { return EventType::WindowResize; }

        int GetWidth() { return m_Width; }
        int GetHeight() { return m_Height; }

    private:
        int m_Width, m_Height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent();
        ~WindowCloseEvent() = default;

        std::string ToString() override;

        EventType GetType() { return EventType::WindowClose; }
    };
}