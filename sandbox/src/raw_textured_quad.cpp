#include "raw_textured_quad.hpp"

#include <glad/glad.h>
#include <stb_image.h>

void RawTexturedQuad::OnAttach()
{
    float vertices[] = {
        // Positions  // TexCoords
        -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
         0.5f, -0.5f, 1.0f, 0.0f, // Bottom-right
         0.5f,  0.5f, 1.0f, 1.0f, // Top-right
        -0.5f,  0.5f, 0.0f, 1.0f  // Top-left
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
    glVertexArrayVertexBuffer(vertexArray, positionBindingIndex, vertexBuffer, 0, sizeof(float) * 4);

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

    const GLuint texCoordAttributeLocation = 1;
    const GLuint texCoordAttributeSize = 2;
    glVertexArrayAttribFormat(
        vertexArray,
        texCoordAttributeLocation, // Matches layout(location = 1) in the vertex shader
        texCoordAttributeSize,     // Number of components (e.g., 2 for vec2)
        GL_FLOAT,                  // Data type (float)
        GL_FALSE,                  // Not normalized
        sizeof(float) * 2          // Offset within the vertex (starts after the position)
    );
    glVertexArrayAttribBinding(vertexArray, texCoordAttributeLocation, positionBindingIndex);
    glEnableVertexArrayAttrib(vertexArray, texCoordAttributeLocation);

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

    // Shader
    const char* vertexShaderSource = R"(
        #version 460 core

        layout(location = 0) in vec2 a_Position;
        layout(location = 1) in vec2 a_TexCoord;

        out vec2 v_TexCoord;

        void main()
        {
            gl_Position = vec4(a_Position, 0.0, 1.0);
            v_TexCoord = a_TexCoord;
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 460 core

        in vec2 v_TexCoord;

        out vec4 color;

        uniform sampler2D u_Texture;

        void main()
        {
            color = texture(u_Texture, v_TexCoord);
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Load the texture using stb_image
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("sandbox/assets/textures/checkerboard.png", &width, &height, &channels, 0);
    UE_CORE_ASSERT(data, "Failed to load texture!");

    GLuint texture;
    const GLuint numberOfTextures = 1;
    // Create the texture object
    glCreateTextures(GL_TEXTURE_2D, numberOfTextures, &texture);
    
    // Allocate memory for the texture
    GLuint levels = 1;
    GLuint format = (channels == 4) ? GL_RGBA8 : GL_RGB8;
    GLuint internalFormat = (channels == 4) ? GL_RGBA : GL_RGB;
    glTextureStorage2D(texture, levels, format, width, height);

    // Set the texture wrapping parameters
    glTextureSubImage2D(
        texture,         // Texture ID
        0,               // Base level (no mipmaps)
        0, 0,            // Start at the top-left corner
        width, height,   // Dimensions of the image
        internalFormat,  // Format of the pixel data
        GL_UNSIGNED_BYTE, // Data type (8-bit per channel)
        data             // Pointer to the pixel data
    );

    // Set the texture filtering parameters
    glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Set the texture wrapping parameters
    glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set the texture unit
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "u_Texture"), 0);

    // Bind the texture to the texture unit
    glBindTextureUnit(0, texture);
}

void RawTexturedQuad::OnDetach()
{
    glDeleteVertexArrays(1, &m_VertexArray);
}

void RawTexturedQuad::OnUpdate(Universe::Timestep ts)
{
    glClearColor(0.1f, 0.1f, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render
    glBindVertexArray(m_VertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void RawTexturedQuad::OnEvent(Universe::Event& event)
{
    UE_CORE_TRACE("{0}", event.ToString());
}