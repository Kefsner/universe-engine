#pragma once

#include "universe/base/base.hpp"
#include "universe/renderer/buffer.hpp"

namespace Universe
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        static Ref<VertexArray> Create();
    };
}