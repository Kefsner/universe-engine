#include "pch.hpp"

#include "universe/core/core.hpp"
#include "universe/renderer/renderer_api.hpp"
#include "universe/renderer/opengl/opengl_renderer_api.hpp"

namespace Universe {

    // Hardcoded to OpenGL for now
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Ref<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
            case RendererAPI::API::None:    UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLRendererAPI>();
        }

        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}