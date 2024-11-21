#include "engine/renderer/renderer.hpp"
#include "engine/logger/logger.hpp"
#include <glad/glad.h>

namespace Universe {

    static unsigned int s_VAO;
    static unsigned int s_VBO;
    static unsigned int s_ShaderProgram;

    static const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    static const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color
        }
    )";

    void Renderer::Init() {
        float vertices[] = { // Positions
             0.0f,  0.5f, 0.0f, // Top
            -0.5f, -0.5f, 0.0f, // Bottom left
             0.5f, -0.5f, 0.0f  // Bottom right
        };

        // Create Vertex Buffer Object (VBO)        
        glGenBuffers(1, &s_VBO);
        // Bind the VBO (Meaning that all subsequent buffer operations will affect this buffer)
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        // Copy the vertices data into the VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*9, vertices, GL_STATIC_DRAW);
        
        // Create Vertex Array Object (VAO)
        glGenVertexArrays(1, &s_VAO);
        glBindVertexArray(s_VAO); 

        // Set the vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind the VBO and VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Compile shaders
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // Link the shaders into a shader program
        s_ShaderProgram = glCreateProgram();
        glAttachShader(s_ShaderProgram, vertexShader);
        glAttachShader(s_ShaderProgram, fragmentShader);
        glLinkProgram(s_ShaderProgram);

        // Delete the shaders as they are linked into the shader program
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Check if the shader program was linked successfully
        int success;
        char infoLog[512];
        glGetProgramiv(s_ShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(s_ShaderProgram, 512, NULL, infoLog);
            UE_CORE_ERROR("Shader program linking failed: {0}", infoLog);
        }

    }

    void Renderer::Shutdown() {}
    void Renderer::BeginScene() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::Submit() {
        glUseProgram(s_ShaderProgram);
        glBindVertexArray(s_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Unbind the VAO
        glBindVertexArray(0);
        glUseProgram(0);
    }

    void Renderer::EndScene() {}

}
