#include "pch.hpp"

#include "universe/base/base.hpp"
#include "universe/renderer/renderer_api.hpp"
#include "universe/renderer/opengl/opengl_renderer_api.hpp"

namespace Universe
{
    Scope<RendererAPI> RendererAPI::Create()
    {
        return CreateScope<OpenGLRendererAPI>();
    }
}