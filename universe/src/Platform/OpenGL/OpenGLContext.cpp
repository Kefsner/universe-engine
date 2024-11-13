#include "UEpch.h"

#include "Universe/Core/Assert.h"
#include "Universe/Core/Log.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Universe {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		UE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		UE_CORE_ASSERT(status, "Failed to initialize Glad!");

		UE_CORE_INFO("OpenGL Info:");
		UE_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		UE_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		UE_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

		UE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Universe requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}