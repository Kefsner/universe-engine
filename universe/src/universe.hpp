#pragma once

// ==================== INCLUDES ====================
#include "universe/application.hpp"
#include "universe/base/logger.hpp"
#include "universe/base/assert.hpp"

#include "universe/events/events.hpp"
#include "universe/events/application_events.hpp"

// ==================== ENTRY POINT ====================
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