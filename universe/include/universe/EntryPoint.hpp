#pragma once

#include "Application.hpp"

#include "core/Logger.hpp"

int main()
{
    Universe::Logger::Init();
    
    UE_CORE_INFO("Creating Universe");
    auto app = Universe::Application::CreateApplication();

    UE_CORE_INFO("Running Universe");
    app->Run();

    UE_CORE_INFO("Destroying Universe");
    delete app;

    return 0;
}