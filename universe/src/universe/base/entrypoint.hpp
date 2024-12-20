#pragma once

#include "universe/application.hpp"
#include "universe/base/logger.hpp"

int main()
{
    Universe::Logger::Init();
    
    UE_CORE_INFO("Creating Universe");
    auto universe = Universe::Create();
    
    UE_CORE_INFO("Running Universe");
    universe->Run();

    UE_CORE_INFO("Destroying Universe");
    delete universe;

    return 0;
}