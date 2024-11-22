#include "pch.hpp"
#include "engine/renderer/vertex_array.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/opengl/opengl_vertex_array.hpp"
#include "engine/logger/logger.hpp"

namespace Universe {

    std::unique_ptr<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None:    
                UE_CORE_ASSERT(false, "RendererAPI::None is not a valid RendererAPI!");
                return nullptr;

            case RendererAPI::OpenGL:
                return std::make_unique<OpenGLVertexArray>();
        }

        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
