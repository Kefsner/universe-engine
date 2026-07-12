#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace Universe
{
    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &m_ID);

        int attributeIndex = 0;
        int attributeSize = 3;
        int bindingIndex = 0;
        glEnableVertexArrayAttrib(m_ID, attributeIndex);
        glVertexArrayAttribFormat(m_ID, attributeIndex, attributeSize, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(m_ID, attributeIndex, bindingIndex);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_ID);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(m_ID);
    }

    void VertexArray::AttachBuffers(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer)
    {
        glVertexArrayVertexBuffer(m_ID, 0, vertexBuffer->GetID(), 0, 3*sizeof(float));
        glVertexArrayElementBuffer(m_ID, indexBuffer->GetID());
    }
}