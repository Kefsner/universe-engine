#include "pch.hpp"
#include "engine/renderer/buffer.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/opengl/opengl_buffer.hpp"
#include "engine/logger/logger.hpp"
#include "engine/core.hpp"

namespace Universe {

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                UE_CORE_ASSERT(false, "RendererAPI::None is not a valid RendererAPI!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        }

        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                UE_CORE_ASSERT(false, "RendererAPI::None is not a valid RendererAPI!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLIndexBuffer>(indices, count);
        }

        UE_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
