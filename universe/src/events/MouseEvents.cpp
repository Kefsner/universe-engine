#include "events/MouseEvents.hpp"

namespace Universe
{
    MouseMoveEvent::MouseMoveEvent(double xpos, double ypos)
        : m_XPos(xpos), m_YPos(ypos)
    {
    }

    std::string MouseMoveEvent::ToString()
    {
        std::string message = std::string("Mouse Move: xPos {");
        message = message + std::to_string(m_XPos) + std::string("}, yPos {");
        message = message + std::to_string(m_YPos) + std::string("}");
        return message;
    }

    MouseButtonEvent::MouseButtonEvent(int key)
        : m_Key(key)
    {
    }

    std::string MouseButtonEvent::ToString()
    {
        std::string message = std::string("Mouse Button: {");
        message = message + std::to_string(m_Key) + std::string("}");
        return message;
    }

    MouseScrollEvent::MouseScrollEvent(double offset)
        : m_Offset(offset)
    {
    }

    std::string MouseScrollEvent::ToString()
    {
        std::string message = std::string("Mouse Scroll: {");
        message = message + std::to_string(m_Offset) + std::string("}");
        return message;
    }
}