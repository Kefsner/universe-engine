#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Universe
{
    struct WindowProps
    {
        int Width;
        int Height;
        const char* Title;
        bool Debug;
    };

    class Window
    {
    public:
        Window(WindowProps props);
        ~Window();

        GLFWwindow* GetNativeWindow() const { return m_NativeWindow; }

        bool ShouldClose();
        void Update();

    private:
        // NOTE: Not sure why I need APIENTRY
        static void APIENTRY DebugCallbackMessage(
            GLenum Source,
            GLenum Type,
            GLuint Id,
            GLenum Severity,
            GLsizei Length,
            const GLchar* Message,
            const void* UserParam
        );

    private:
        bool m_DebugMode;
        GLFWwindow* m_NativeWindow;
    };
}