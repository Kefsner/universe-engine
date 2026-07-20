#include "core/Logger.hpp"

#include "events/KeyEvents.hpp"

#include <string>

namespace Universe
{
    KeyPressEvent::KeyPressEvent(int key)
        : m_Key(key)
    {
    }

    std::string KeyPressEvent::ToString()
    {
        std::string key = std::to_string(m_Key);
        return std::string("Key Pressed {") + key + "}";
    }

    KeyReleaseEvent::KeyReleaseEvent(int key)
        : m_Key(key)
    {
    }

    std::string KeyReleaseEvent::ToString()
    {
        std::string key = std::to_string(m_Key);
        return std::string("Key Released {") + key + "}";
    }

    KeyRepeatEvent::KeyRepeatEvent(int key)
        : m_Key(key)
    {
    }
    
    std::string KeyRepeatEvent::ToString()
    {
        std::string key = std::to_string(m_Key);
        return std::string("Key Repeat {") + key + "}";
    }
}