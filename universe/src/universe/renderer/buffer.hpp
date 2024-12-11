#pragma once

#include <cstdint>

#include "universe/core/core.hpp"
#include "universe/core/logger.hpp"
#include "universe/core/assert.hpp"

namespace Universe {
    
    enum class ShaderDataType
    {
        None = 0,
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Int, Int2, Int3, Int4,
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:    return 4;
        case ShaderDataType::Float2:   return 4 * 2;
        case ShaderDataType::Float3:   return 4 * 3;
        case ShaderDataType::Float4:   return 4 * 4;
        case ShaderDataType::Mat3:     return 4 * 3 * 3;
        case ShaderDataType::Mat4:     return 4 * 4 * 4;
        case ShaderDataType::Int:      return 4;
        case ShaderDataType::Int2:     return 4 * 2;
        case ShaderDataType::Int3:     return 4 * 3;
        case ShaderDataType::Int4:     return 4 * 4;
        case ShaderDataType::Bool:     return 1;
        }

        UE_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    struct BufferElement
    {
        BufferElement(ShaderDataType type, const std::string& name)
            : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0) {}
        ~BufferElement() = default;

        std::string name;       // Name of the element
        ShaderDataType type;    // Type of the element
        uint32_t size;          // Size of the element in bytes
        uint32_t offset;        // Offset of the element in the buffer
        bool normalized;        // Whether the element is normalized

        uint32_t GetComponentCount() const
        {
            switch (type)
            {
            case ShaderDataType::Float:    return 1;
            case ShaderDataType::Float2:   return 2;
            case ShaderDataType::Float3:   return 3;
            case ShaderDataType::Float4:   return 4;
            case ShaderDataType::Mat3:     return 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4;
            case ShaderDataType::Int:      return 1;
            case ShaderDataType::Int2:     return 2;
            case ShaderDataType::Int3:     return 3;
            case ShaderDataType::Int4:     return 4;
            case ShaderDataType::Bool:     return 1;
            }

            UE_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() {} // TODO: Understand why this is needed
        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_Elements(elements) { CalculateOffsetsAndStride(); }
        ~BufferLayout() = default;

        const std::vector<BufferElement>& GetElements() const { return m_Elements; }
        uint32_t GetStride() const { return m_Stride; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

    private:
        std::vector<BufferElement> m_Elements;  // Vector of buffer elements
        uint32_t m_Stride = 0;                  // Stride of the buffer layout

        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements)
            {
                element.offset = offset;
                offset += element.size;
                m_Stride += element.size;
            }
        }
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;
        
        virtual void Bind() const = 0;
        
        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        virtual void SetData(const void* data, uint32_t size) = 0;

        static Ref<VertexBuffer> Create(uint32_t size);
        static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;
        virtual void Bind() const = 0;
        virtual uint32_t GetCount() const = 0;

        static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
    };
}