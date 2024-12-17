#pragma once

#include <GLFW/glfw3.h>

#include "universe/base/base.hpp"
#include "universe/renderer/graphics_context.hpp"

namespace Universe
{
    class OpenGLGraphicsContext : public GraphicsContext
    {
    public:
        OpenGLGraphicsContext(GLFWwindow* window);

        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_Window;
    };
}