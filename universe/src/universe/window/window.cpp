#include "pch.hpp"

#include "universe/window/window.hpp"

// Include specific implementations
#if defined(UE_PLATFORM_WINDOWS) || defined(UE_PLATFORM_LINUX)
    #include "universe/window/glfw_window.hpp"
#endif

namespace Universe {

    Scope<Window> Window::Create(const WindowProps& props)
    {
        #if defined(UE_PLATFORM_WINDOWS) || defined(UE_PLATFORM_LINUX)
            return std::make_unique<GLFWWindowWrapper>(props);
        #else
            UE_CORE_ASSERT(false, "Unknown platform!");
            return nullptr;
        #endif
    }

}
