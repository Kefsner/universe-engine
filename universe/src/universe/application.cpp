#include "universe/application.hpp"
#include <iostream>

namespace Universe
{
    Application::Application()
    {
        // Initialize the application
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
            std::cout << "Running the application" << std::endl;

            // Exit the application
            if (!m_IsRunning)
            {
                std::cout << "Exiting the application" << std::endl;
            }
        }
        
    }
}