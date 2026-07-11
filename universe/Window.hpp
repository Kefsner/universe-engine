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

        GLFWwindow* GetNativeWindow() { return m_NativeWindow; }

        bool ShouldClose();
        void Update();

    private:
        bool m_DebugMode;
        GLFWwindow* m_NativeWindow;
    };
}