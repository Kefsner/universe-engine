#include "pch.hpp"

#include "universe/application.hpp"
#include "universe/base/logger.hpp"

namespace Universe
{
    Application::Application()
    {
        
    }

    Application::~Application()
    {
        // Shutdown the application
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            // Run the application
            UE_CORE_TRACE("Running the application");

            // Exit the application
            if (!m_IsRunning)
            {
                UE_CORE_TRACE("Exiting the application");
            }
        }
        
    }
}