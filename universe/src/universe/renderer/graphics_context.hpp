#pragma once

#include <GLFW/glfw3.h>

#include "universe/base/base.hpp"

namespace Universe
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;

        virtual void SwapBuffers() = 0;
        virtual void UpdateViewport() = 0;

        static Scope<GraphicsContext> Create(void* nativeWindow);
    };
}