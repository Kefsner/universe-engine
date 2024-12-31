#pragma once

#include <glm/glm.hpp>

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

    class TextureAtlas
    {
    public:
        TextureAtlas(Ref<Texture2D>& texture, uint32_t rows, uint32_t columns);

        std::array<glm::vec2, 4> CalculateTextureCoords(uint32_t index);

        Ref<Texture2D> GetTexture() const { return m_Texture; }
        uint32_t GetRows() const { return m_Rows; }
        uint32_t GetColumns() const { return m_Columns; }

        static Ref<TextureAtlas> Create(Ref<Texture2D>& texture, uint32_t rows, uint32_t columns);

    private:
        Ref<Texture2D> m_Texture;
        uint32_t m_Rows, m_Columns;
    };
}