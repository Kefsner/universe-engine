#pragma once

#include "universe/base/base.hpp"

namespace Universe
{
    class Texture2D
    {
    public:
        virtual ~Texture2D() = default;

        virtual int32_t GetWidth() const = 0;
        virtual int32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        static Ref<Texture2D> Create(std::string path);
    };
}