#include "pch.hpp"
#include "engine/renderer/buffer.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/opengl/opengl_buffer.hpp"
#include "engine/logger/logger.hpp"

namespace Universe {

    std::unique_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:
                UE_CORE_ASSERT(false, "RendererAPI::None is not a valid RendererAPI!");
                return nullptr;
            case RendererAPI::OpenGL:
                return std::make_unique<OpenGLVertexBuffer>(vertices, size);
        }

        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}