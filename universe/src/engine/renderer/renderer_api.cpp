#include "pch.hpp"
#include "engine/core.hpp"
#include "engine/renderer/renderer_api.hpp"
#include "engine/renderer/opengl/opengl_renderer_api.hpp"

namespace Universe {

    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Ref<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
            case RendererAPI::API::None:    UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLRendererAPI>();
        }

        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}