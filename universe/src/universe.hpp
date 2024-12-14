#pragma once

// ==================== INCLUDES ====================
#include "universe/application.hpp"


// ==================== ENTRY POINT ====================
int main()
{
    auto universe = Universe::Create();
    
    universe->Run();

    delete universe;

    return 0;
}