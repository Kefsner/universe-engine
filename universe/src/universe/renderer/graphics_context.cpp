#include "pch.hpp"

#include <GLFW/glfw3.h>

#include "universe/base/base.hpp"
#include "universe/renderer/graphics_context.hpp"
#include "universe/renderer/opengl/opengl_graphics_context.hpp"

namespace Universe
{
    Scope<GraphicsContext> GraphicsContext::Create(void* nativeWindow)
    {
        return CreateScope<OpenGLGraphicsContext>(static_cast<GLFWwindow*>(nativeWindow));
    }
}