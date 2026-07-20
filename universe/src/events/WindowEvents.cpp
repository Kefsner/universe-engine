#include "events/WindowEvents.hpp"

namespace Universe
{
    WindowResizeEvent::WindowResizeEvent(int width, int height)
        : m_Width(width), m_Height(height)
    {
    }

    std::string WindowResizeEvent::ToString()
    {
        std::string message = std::string("Window Resized: Width {");
        message = message + std::to_string(m_Width) + std::string("}, Height {");
        message = message + std::to_string(m_Height) + std::string("}");
        return message;
    }

    WindowCloseEvent::WindowCloseEvent()
    {
    }

    std::string WindowCloseEvent::ToString()
    {
        return std::string("Window Close Event");
    }
}