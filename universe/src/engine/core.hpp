#pragma once

#include <memory>
#include <csignal>

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

// Bind Macro
#define UE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)

namespace Universe {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}
