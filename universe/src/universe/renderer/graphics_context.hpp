#pragma once

#include <GLFW/glfw3.h>

#include "universe/base/base.hpp"

namespace Universe
{
    class GraphicsContext
    {
    public:
        virtual void SwapBuffers() = 0;

        static Scope<GraphicsContext> Create(void* nativeWindow);
    };
}