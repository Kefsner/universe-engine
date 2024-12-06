#include "pch.hpp"
#include "universe/renderer/vertex_array.hpp"
#include "universe/renderer/renderer.hpp"
#include "universe/renderer/opengl/opengl_vertex_array.hpp"
#include "universe/core/logger.hpp"
#include "universe/core/core.hpp"

namespace Universe {

    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:    
                UE_CORE_ASSERT(false, "RendererAPI::None is not a valid RendererAPI!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLVertexArray>();
        }
        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
