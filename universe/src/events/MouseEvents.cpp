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
}