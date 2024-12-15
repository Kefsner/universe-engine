#pragma once

// ==================== INCLUDES ====================
#include "universe/application.hpp"
#include "universe/base/logger.hpp"
#include "universe/base/assert.hpp"

// ==================== ENTRY POINT ====================
int main()
{
    Universe::Logger::Init();
    
    auto universe = Universe::Create();
    
    universe->Run();

    delete universe;

    return 0;
}