#include "quad.hpp"

#include <glad/glad.h>

void Quad::OnAttach()
{
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    // Create a buffer
    Universe::Ref<Universe::VertexBuffer> vertexBuffer;
    vertexBuffer = Universe::VertexBuffer::Create(vertices, sizeof(vertices));

    // Create a vertex array
    m_VertexArray = Universe::VertexArray::Create();

    // Add the buffer to the vertex array
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    // Create an index buffer
    uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
    m_IndexBufferCount = sizeof(indices) / sizeof(uint32_t);
    Universe::Ref<Universe::IndexBuffer> indexBuffer;
    indexBuffer = Universe::IndexBuffer::Create(indices, m_IndexBufferCount);

    // Add the index buffer to the vertex array
    m_VertexArray->SetIndexBuffer(indexBuffer);
}

void Quad::OnDetach()
{
}

void Quad::OnUpdate(Universe::Timestep ts)
{
    Universe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Universe::RenderCommand::Clear();
    m_VertexArray->Bind();
    Universe::RenderCommand::DrawIndexed(GL_TRIANGLES, m_IndexBufferCount);
}

void Quad::OnEvent(Universe::Event& event)
{
    UE_CORE_TRACE("{0}", event.ToString());
}