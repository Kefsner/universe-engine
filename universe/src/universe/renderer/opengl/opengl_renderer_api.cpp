#include "pch.hpp"

#include <glad/glad.h>

#include "universe/renderer/opengl/opengl_renderer_api.hpp"

namespace Universe
{
    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::DrawArrays(uint32_t mode, uint32_t first, uint32_t count)
    {
        glDrawArrays(mode, first, count);
    }
}