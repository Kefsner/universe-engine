#pragma once

#include "universe/core/core.hpp"

namespace Universe {

    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static Ref<GraphicsContext> Create(void* nativeWindow);
    };
}
