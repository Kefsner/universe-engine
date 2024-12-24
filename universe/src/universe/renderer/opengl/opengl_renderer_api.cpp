#include "pch.hpp"

#include <glad/glad.h>

#include "universe/renderer/opengl/opengl_renderer_api.hpp"

namespace Universe
{
    OpenGLRendererAPI::OpenGLRendererAPI()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::DrawArrays(uint32_t first, uint32_t count)
    {
        glDrawArrays(GL_TRIANGLES, first, count);
    }

    void OpenGLRendererAPI::DrawIndexed(uint32_t count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
}