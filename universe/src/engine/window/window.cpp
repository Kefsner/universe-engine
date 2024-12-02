#include "pch.hpp"
#include "engine/core.hpp"
#include "engine/window/window.hpp"

// Include specific implementations
#if defined(UE_PLATFORM_WINDOWS) || defined(UE_PLATFORM_LINUX)
    #include "engine/window/glfw_window.hpp"
#endif

namespace Universe {

    Window* Window::Create(const WindowProps& props) {
        #if defined(UE_PLATFORM_WINDOWS) || defined(UE_PLATFORM_LINUX)
            return new GLFWWindowWrapper(props);
        #else
            UE_CORE_ASSERT(false, "Unknown platform!");
            return nullptr;
        #endif
    }

}
