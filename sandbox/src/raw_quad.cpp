#include "raw_quad.hpp"

#include <glad/glad.h>

void RawQuad::OnAttach()
{
    float vertices[] = {
        // Positions
        -0.5f, -0.5f, // Bottom-left
        0.5f, -0.5f, // Bottom-right
        0.5f,  0.5f, // Top-right
        -0.5f,  0.5f  // Top-left
    };

    // Create a buffer
    GLuint vertexBuffer;
    const GLuint numberOfVertexBuffers = 1;
    glCreateBuffers(numberOfVertexBuffers, &vertexBuffer);
    // Allocate memory for the buffer
    glNamedBufferData(vertexBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create a vertex array
    GLuint vertexArray;
    const GLuint numberOfVertexArrays = 1;
    glCreateVertexArrays(numberOfVertexArrays, &vertexArray);

    // Bind the vertex array
    glBindVertexArray(vertexArray);

    // Bind the buffer to the vertex array
    GLuint positionBindingIndex = 0;
    glVertexArrayVertexBuffer(vertexArray, positionBindingIndex, vertexBuffer, 0, sizeof(float) * 2);

    // Enable the vertex attribute
    const GLuint positionAttributeLocation = 0;
    const GLuint positionAttributeSize = 2;
    glVertexArrayAttribFormat(
        vertexArray,
        positionAttributeLocation, // Matches layout(location = 0) in the vertex shader
        positionAttributeSize,     // Number of components (e.g., 2 for vec2)
        GL_FLOAT,                  // Data type (float)
        GL_FALSE,                  // Not normalized
        0                          // Offset within the vertex (starts at the beginning)
    );
    glVertexArrayAttribBinding(vertexArray, positionAttributeLocation, positionBindingIndex);
    glEnableVertexArrayAttrib(vertexArray, positionAttributeLocation);

    // Create an index buffer
    uint32_t indices[] = {
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
    };

    GLuint indexBuffer;
    const GLuint numberOfIndexBuffers = 1;
    glCreateBuffers(numberOfIndexBuffers, &indexBuffer);
    glNamedBufferData(indexBuffer, sizeof(indices), indices, GL_STATIC_DRAW);

    // Bind the index buffer to the vertex array
    glVertexArrayElementBuffer(vertexArray, indexBuffer);

    m_VertexArray = vertexArray; // For later use in rendering
    m_IndexCount = sizeof(indices) / sizeof(uint32_t);

    glClearColor(0.1f, 0.1f, 0.1f, 1);
}

void RawQuad::OnDetach()
{
}

void RawQuad::OnUpdate(Universe::Timestep ts)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(m_VertexArray);
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
}

void RawQuad::OnEvent(Universe::Event& event)
{
    UE_CORE_TRACE("{0}", event.ToString());
}

