#include "pch.hpp"

#include "universe/renderer/buffer.hpp"
#include "universe/renderer/opengl/opengl_buffer.hpp"

namespace Universe
{
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        return CreateRef<OpenGLVertexBuffer>(vertices, size);
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        return CreateRef<OpenGLIndexBuffer>(indices, count);
    }
}