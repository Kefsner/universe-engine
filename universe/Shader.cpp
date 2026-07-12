#include "Shader.hpp"

#include <spdlog/spdlog.h>

namespace Universe
{
    Shader::Shader()
    {
        const char* vertexShaderSrc = R"(
            #version 460 core

            layout (location = 0) in vec3 pos;

            void main()
            {
                gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
            }
        )";

        const char* fragmentShaderSrc = R"(
            #version 460 core

            out vec4 color;

            void main()
            {
                color = vec4(0.8, 0.8, 0.2, 1.0);
            }
        )";

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
        glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);

        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);

        CheckCompilationStatus(vertexShader);
        CheckCompilationStatus(fragmentShader);

        m_ShaderProgram = glCreateProgram();

        glAttachShader(m_ShaderProgram, vertexShader);
        glAttachShader(m_ShaderProgram, fragmentShader);
        glLinkProgram(m_ShaderProgram);

        CheckLinkingStatus();

        glUseProgram(m_ShaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        spdlog::info("Shaders created successfully.");
    };

    void Shader::Bind()
    {
        glUseProgram(m_ShaderProgram);
    }

    void Shader::CheckCompilationStatus(GLuint shader)
    {
        int success;
        char infoLog[512];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            spdlog::warn("Failed to compile shader");
            glGetShaderInfoLog(shader, 512, 0, infoLog);
            spdlog::warn("InfoLog: {}", infoLog);
        }
    }

    void Shader::CheckLinkingStatus()
    {
        int success;
        char infoLog[512];

        glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);

        if (!success)
        {
            spdlog::warn("Failed to link shader");
            glGetShaderInfoLog(m_ShaderProgram, 512, 0, infoLog);
            spdlog::warn("InfoLog: {}", infoLog);
        }
    }
}
