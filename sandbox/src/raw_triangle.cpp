#include "raw_triangle.hpp"

#include <glad/glad.h>

void RawTriangle::OnAttach()
{
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f
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

    m_VertexArray = vertexArray; // For later use in rendering

    glClearColor(0.1f, 0.1f, 0.1f, 1);
}

void RawTriangle::OnDetach()
{
}

void RawTriangle::OnUpdate(Universe::Timestep ts)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(m_VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void RawTriangle::OnEvent(Universe::Event& event)
{
    UE_CORE_TRACE("{0}", event.ToString());
}
