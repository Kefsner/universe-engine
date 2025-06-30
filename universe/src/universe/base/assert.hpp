#pragma once

#if defined(_MSC_VER)
    #define UE_DEBUGBREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
    #include <signal.h>
    #define UE_DEBUGBREAK() raise(SIGTRAP)
#else
    #define UE_DEBUGBREAK() ((void)0)
#endif


#if defined(UE_DEBUG)
    #define UE_ASSERT(x, ...) { if(!(x)) { UE_ERROR("Assertion Failed: {0}", __VA_ARGS__); UE_DEBUGBREAK(); } }
    #define UE_CORE_ASSERT(x, ...) { if(!(x)) { UE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); UE_DEBUGBREAK(); } }
#else
    #define UE_ASSERT(x, ...)
    #define UE_CORE_ASSERT(x, ...)
#endif