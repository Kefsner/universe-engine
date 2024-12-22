#pragma once

#include "universe/base/base.hpp"

namespace Universe
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetVertexBufferID() const = 0;

        static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
    };
}