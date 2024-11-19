#include "pch.hpp"
#include "engine/window/window.hpp"

// Include specific implementations
#ifdef UE_PLATFORM_WINDOWS
    #include "engine/window/glfw_window_wrapper.hpp"
#endif

namespace Universe {
    Window* Window::Create(const WindowProps& props) {
        #ifdef UE_PLATFORM_WINDOWS
            return new GLFWWindowWrapper(props);
        #else
            UE_CORE_ASSERT(false, "Unknown platform!");
            return nullptr;
        #endif
    }
}
