#include "pch.hpp"

#include <glad/glad.h>

#include "universe/renderer/opengl/opengl_context.hpp"
#include "universe/core/assert.hpp"
#include "universe/core/logger.hpp"


namespace Universe {
    
    OpenGLContext::OpenGLContext(GLFWwindow* window) : m_window(window) {}

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        UE_CORE_ASSERT(status, "Could not initialize Glad!");

		UE_CORE_INFO("OpenGL Info:");
		UE_CORE_INFO(" --Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		UE_CORE_INFO(" --Rrenderer: {0}", (const char*)glGetString(GL_RENDERER));
		UE_CORE_INFO(" --Version: {0}", (const char*)glGetString(GL_VERSION));
		UE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Universe requires at least OpenGL version 4.5!");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_window);
    }
}
