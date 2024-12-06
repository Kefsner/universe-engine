#pragma once

#if defined(UE_DEBUG)
    // Cross-platform debug break function
    inline void trigger_debug_break() {
    #if defined(_WIN32)
        __debugbreak();
    #elif defined(__linux__)
        raise(SIGTRAP);
    #endif
    }
    // Assert Macros
    #define UE_ASSERT(x, ...) { if(!(x)) { UE_ERROR("Assertion Failed: {0}", __VA_ARGS__); trigger_debug_break(); } }
    #define UE_CORE_ASSERT(x, ...) { if(!(x)) { UE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); trigger_debug_break(); } }
#else 
    #define UE_ASSERT(x, ...)
    #define UE_CORE_ASSERT(x, ...)
#endif
