#pragma once

#include "universe/base/base.hpp"
#include "universe/base/assert.hpp"
#include "universe/renderer/shader.hpp"

namespace Universe
{
    struct BufferElement
    {
        // Populated in the constructor
        ShaderDataType type;
        std::string name;
        bool normalized;

        // Populated in BufferLayout::CalculateElementOffsetAndLayoutStride
        uint32_t size;
        uint32_t numberOfComponents;
        uint32_t offset; // Updated in BufferLayout::CalculateElementOffsetAndLayoutStride

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : name(name), type(type), normalized(normalized)
        {
            size = ShaderDataTypeSize(type);
            numberOfComponents = GetComponentCount(type);
        }

        static uint32_t ShaderDataTypeSize(ShaderDataType type)
        {
            switch (type)
            {
                case ShaderDataType::Float:  return sizeof(float);
                case ShaderDataType::Float2: return sizeof(float) * 2;
                case ShaderDataType::Float3: return sizeof(float) * 3;
                case ShaderDataType::Float4: return sizeof(float) * 4;
                case ShaderDataType::Int:    return sizeof(uint32_t);
                case ShaderDataType::Int2:   return sizeof(uint32_t) * 2;
                case ShaderDataType::Int3:   return sizeof(uint32_t) * 3;
                case ShaderDataType::Int4:   return sizeof(uint32_t) * 4;
                case ShaderDataType::Bool:   return sizeof(bool);
            }

            UE_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }


        static uint32_t GetComponentCount(ShaderDataType type)
        {
            switch (type)
            {
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Bool:   return 1;
            }

            UE_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_Elements(elements), m_Stride(CalculateElementOffsetAndLayoutStride()) {}

        uint32_t GetStride() const { return m_Stride; }
        uint32_t GetElementCount() const { return m_Elements.size(); }

        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride;

        uint32_t CalculateElementOffsetAndLayoutStride()
        {
            uint32_t stride = 0;
            for (auto& element : m_Elements)
            {
                element.offset = stride;
                stride += element.size;
            }
            return stride;
        }
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetVertexBufferID() const = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetIndexBufferID() const = 0;
        virtual uint32_t GetCount() const = 0;

        static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
    };
}