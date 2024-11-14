#pragma once

#include "engine/renderer/graphics_context.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Universe {

    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };

}