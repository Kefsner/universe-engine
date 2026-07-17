#include "renderer/VertexArray.hpp"
#include "renderer/VertexBuffer.hpp"
#include "renderer/IndexBuffer.hpp"

#include <spdlog/spdlog.h>

namespace Universe
{
    
    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &m_ID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_ID);
    }

    void VertexArray::SetAttributes()
    {
        glEnableVertexArrayAttrib(m_ID, 0);
        glVertexArrayAttribFormat(m_ID, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(m_ID, 0, 0);
        // int attribute1Index = 0;
        // int attribute1Size = 3;
        // int bindingIndex = 0; // One slot for each possible buffer it seems.
        // glEnableVertexArrayAttrib(m_ID, attribute1Index);
        // glVertexArrayAttribFormat(m_ID, attribute1Index, attribute1Size, GL_FLOAT, GL_FALSE, 0);
        // glVertexArrayAttribBinding(m_ID, attribute1Index, bindingIndex);
        // spdlog::info("Attribute 1 ready");

        // int attribute2Index = 1;
        // int attribute2Size = 3;
        // glEnableVertexArrayAttrib(m_ID, attribute2Index);
        // glVertexArrayAttribFormat(m_ID, attribute2Index, attribute2Size, GL_FLOAT, GL_FALSE, 3*sizeof(float));
        // glVertexArrayAttribBinding(m_ID, attribute2Index, bindingIndex); // Same bind because attribute 2 comes from the same buffer.
        // spdlog::info("Attribute 2 ready");

        // int attribute3Index = 2;
        // int attribute3Size = 2;
        // glEnableVertexArrayAttrib(m_ID, attribute3Index);
        // glVertexArrayAttribFormat(m_ID, attribute3Index, attribute3Size, GL_FLOAT, GL_FALSE, 6*sizeof(float));
        // glVertexArrayAttribBinding(m_ID, attribute3Index, bindingIndex);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(m_ID);
    }

    void VertexArray::AttachBuffers(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer)
    {
        glVertexArrayVertexBuffer(m_ID, 0, vertexBuffer.GetID(), 0, vertexBuffer.GetStride());
        glVertexArrayElementBuffer(m_ID, indexBuffer.GetID());
    }
}