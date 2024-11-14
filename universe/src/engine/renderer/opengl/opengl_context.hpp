#pragma once

#include "engine/renderer/graphics_context.hpp"

namespace Universe {

    class OpenGLContext : public GraphicsContext {
    public:
        virtual void Init() override;
        virtual void SwapBuffers() override;
    };

}