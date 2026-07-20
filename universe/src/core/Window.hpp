#pragma once

#include "events/Event.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>

namespace Universe
{
    using EventCallbackFn = std::function<void(Event&)>;
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

        void SetEventCallbackFn(EventCallbackFn callback);

        void Update();

        void OnResize(int width, int height);

    private:
        void SetEventCallbacks();

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
        WindowProps m_Props;
        EventCallbackFn m_EventCallbackFn;
    };
}