#include "pch.hpp"

#include "universe/core/core.hpp"
#include "universe/core/assert.hpp"
#include "universe/renderer/graphics_context.hpp"
#include "universe/renderer/opengl/opengl_context.hpp"

namespace Universe {

    #define UE_API_OPENGL

    Ref<GraphicsContext> GraphicsContext::Create(void* nativeWindow)
    {
        // Add logic to create the appropriate graphics context based on the platform
        // I mean, both OpenGL and Vulkan can be context options for GLFW
        // But for now, we will just return an OpenGL context
        // Also, this needs to be aware that the nativeWindow could be other than GLFWwindow TODO
        // Inside OpenGLContext there are GLFW specific calls
        #if defined(UE_API_OPENGL)
            return std::make_shared<OpenGLContext>(static_cast<GLFWwindow*>(nativeWindow));
        #else
            UE_CORE_ASSERT(false, "Unknown API!");
            return nullptr;
        #endif
    }
}