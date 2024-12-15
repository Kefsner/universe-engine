#pragma once

#if defined(UE_DEBUG)
    #define UE_ASSERT(x, ...) { if(!(x)) { UE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define UE_CORE_ASSERT(x, ...) { if(!(x)) { UE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define UE_ASSERT(x, ...)
    #define UE_CORE_ASSERT(x, ...)
#endif