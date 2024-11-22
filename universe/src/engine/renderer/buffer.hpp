#pragma once

#include <cstdint>

namespace Universe {

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;

        static std::unique_ptr<VertexBuffer> Create(float* vertices, uint32_t size);
    };
}