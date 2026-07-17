#include "Application.hpp"

#include "core/Logger.hpp"

int main()
{
    Universe::Logger::Init();
    
    UE_CORE_LOGGER("Creating Universe");
    auto app = Universe::Application::CreateApplication();

    UE_CORE_LOGGER("Running Universe");
    app->Run();

    UE_CORE_LOGGER("Destroying Universe");
    delete app;

    return 0;
}