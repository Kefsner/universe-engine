#pragma once

#include "universe/base/base.hpp"

namespace Universe
{
    enum class ImageFormat
    {
        None = 0, RGBA8
    };

    struct TextureSpecification
    {
        uint32_t width = 1;
        uint32_t height = 1;
        ImageFormat format = ImageFormat::RGBA8;
    };

    class Texture2D
    {
    public:
        virtual ~Texture2D() = default;

        virtual int32_t GetWidth() const = 0;
        virtual int32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual void SetData(void* data, uint32_t size) = 0;

        static Ref<Texture2D> Create(std::string path);
        static Ref<Texture2D> Create(TextureSpecification spec);
    };
}