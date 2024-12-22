#include "triangle.hpp"

#include <glad/glad.h>

void Triangle::OnAttach()
{
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f
    };

    // Create a buffer
    Universe::Ref<Universe::VertexBuffer> vertexBuffer;
    vertexBuffer = Universe::VertexBuffer::Create(vertices, sizeof(vertices));

    // Create a vertex array
    m_VertexArray = Universe::VertexArray::Create();

    m_VertexArray->AddVertexBuffer(vertexBuffer);
}

void Triangle::OnDetach()
{
}

void Triangle::OnUpdate(Universe::Timestep ts)
{
    Universe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Universe::RenderCommand::Clear();
    m_VertexArray->Bind();
    Universe::RenderCommand::DrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::OnEvent(Universe::Event& event)
{
    UE_CORE_TRACE("{0}", event.ToString());
}