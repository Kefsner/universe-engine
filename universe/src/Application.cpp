#include "Application.hpp"
#include "core/Logger.hpp"

namespace Universe
{
    Application::Application()
    {
        m_IsRunning = true;
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            UE_CORE_LOGGER("Cool bro!");
            m_IsRunning = false;
        }
    }
}
