#pragma once

#include <GLFW/glfw3.h>

#include "universe/renderer/graphics_context.hpp"

namespace Universe {

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* window);
        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_window;
    };

}