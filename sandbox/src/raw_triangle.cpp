#include "raw_triangle.hpp"

#include <glad/glad.h>

void RawTriangle::OnAttach()
{
    float vertices[] = {
        // Positions  // Colors
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // Bottom-left
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Bottom-right
         0.0f,  0.5f, 0.0f, 0.0f, 1.0f // Top
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
    glVertexArrayVertexBuffer(vertexArray, positionBindingIndex, vertexBuffer, 0, sizeof(float) * 5);

    // Enable the vertex attribute
    // Position
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

    // Color
    const GLuint colorAttributeLocation = 1;
    const GLuint colorAttributeSize = 3;
    glVertexArrayAttribFormat(
        vertexArray,
        colorAttributeLocation, // Matches layout(location = 1) in the vertex shader
        colorAttributeSize,     // Number of components (e.g., 3 for vec3)
        GL_FLOAT,               // Data type (float)
        GL_FALSE,               // Not normalized
        sizeof(float) * 2       // Offset within the vertex (starts after the position)
    );
    glVertexArrayAttribBinding(vertexArray, colorAttributeLocation, positionBindingIndex);
    glEnableVertexArrayAttrib(vertexArray, colorAttributeLocation);

    m_VertexArray = vertexArray; // For later use in rendering

    glClearColor(0.1f, 0.1f, 0.1f, 1);

    // Shader
    const char* vertexShaderSource = R"(
        #version 460 core

        layout(location = 0) in vec2 a_Position;
        layout(location = 1) in vec3 a_Color;

        out vec4 v_Color;

        void main()
        {
            gl_Position = vec4(a_Position, 0.0, 1.0);
            v_Color = vec4(a_Color, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 460 core

        in vec4 v_Color;

        out vec4 color;

        void main()
        {
            color = vec4(v_Color);
        }
    )";

    // Create the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLsizei numberOfStrings = 1;
    const GLint* stringLengths = nullptr;
    glShaderSource(vertexShader, numberOfStrings, &vertexShaderSource, stringLengths);
    glCompileShader(vertexShader);

    // Create the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, numberOfStrings, &fragmentShaderSource, stringLengths);
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
    // Called here because there is only one shader program.
    // Otherwise, call it in the render loop for alternative shader programs as needed
    glUseProgram(shaderProgram);
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
