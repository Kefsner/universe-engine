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
        // TODO: Automate with a Buffer Layout
        glEnableVertexArrayAttrib(m_ID, 0);
        glVertexArrayAttribFormat(m_ID, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(m_ID, 0, 0);

        glEnableVertexArrayAttrib(m_ID, 1);
        glVertexArrayAttribFormat(m_ID, 1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float));
        glVertexArrayAttribBinding(m_ID, 1, 0);

        glEnableVertexArrayAttrib(m_ID, 2);
        glVertexArrayAttribFormat(m_ID, 2, 2, GL_FLOAT, GL_FALSE, 6*sizeof(float));
        glVertexArrayAttribBinding(m_ID, 2, 0);
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