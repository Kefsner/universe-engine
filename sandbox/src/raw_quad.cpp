#include "raw_quad.hpp"

#include <glad/glad.h>

void RawQuad::OnAttach()
{
    float vertices[] = {
        // Positions  // Colors
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom-right
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, // Top-right
        -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f  // Top-left
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

    // Bind the buffer to the vertex array
    GLuint positionBindingIndex = 0;
    glVertexArrayVertexBuffer(vertexArray, positionBindingIndex, vertexBuffer, 0, sizeof(float) * 6);

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

    const GLuint colorAttributeLocation = 1;
    const GLuint colorAttributeSize = 4;
    glVertexArrayAttribFormat(
        vertexArray,
        colorAttributeLocation, // Matches layout(location = 1) in the vertex shader
        colorAttributeSize,     // Number of components (e.g., 4 for vec4)
        GL_FLOAT,               // Data type (float)
        GL_FALSE,               // Not normalized
        sizeof(float) * 2       // Offset within the vertex (starts after the position)
    );
    glVertexArrayAttribBinding(vertexArray, colorAttributeLocation, positionBindingIndex);
    glEnableVertexArrayAttrib(vertexArray, colorAttributeLocation);

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

    // Shader
    const char* vertexShaderSource = R"(
        #version 460 core

        layout(location = 0) in vec2 a_Position;
        layout(location = 1) in vec4 a_Color;

        out vec4 v_Color;

        void main()
        {
            gl_Position = vec4(a_Position, 0.0, 1.0);
            v_Color = a_Color;
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 460 core

        in vec4 v_Color;

        out vec4 color;

        void main()
        {
            color = v_Color;
        }
    )";

    // Create the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Create the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Create the shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // We can add a code snippet here to check if the shaders compiled and linked successfully

    // Delete the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Use the shader program
    glUseProgram(shaderProgram);
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

