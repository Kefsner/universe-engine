#include "pch.hpp"
#include "engine/renderer/vertex_array.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/opengl/opengl_vertex_array.hpp"
#include "engine/logger/logger.hpp"
#include "engine/core.hpp"

namespace Universe {

    Ref<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:    
                UE_CORE_ASSERT(false, "RendererAPI::None is not a valid RendererAPI!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLVertexArray>();
        }

        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
