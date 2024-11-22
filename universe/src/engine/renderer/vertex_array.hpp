
#pragma once
#include "engine/renderer/buffer.hpp"

namespace Universe {

    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;

        static std::unique_ptr<VertexArray> Create();
    };
}