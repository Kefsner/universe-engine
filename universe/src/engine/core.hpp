#include <memory>

// Assert Macro
#define UE_ASSERT(x, ...) { if(!(x)) { UE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define UE_CORE_ASSERT(x, ...) { if(!(x)) { UE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

// Bind Macro
#define UE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)

namespace Universe {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}