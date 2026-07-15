#include "renderer/Shader.hpp"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Universe
{
    Shader::Shader()
    {
        const char* vertexShaderSrc = R"(
            #version 460 core

            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aColor;
            layout (location = 2) in vec2 aTexCoord;

            uniform mat4 u_Transform;
            
            out vec4 Color;
            out vec2 TexCoord;

            void main()
            {
                gl_Position = u_Transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
                Color = vec4(aColor, 1.0);
                TexCoord = aTexCoord;
            }
        )";

        const char* fragmentShaderSrc = R"(
            #version 460 core
            
            in vec4 Color;
            in vec2 TexCoord;
            out vec4 FragColor;

            uniform sampler2D u_Textures[32];
            uniform int textureIndex;

            void main()
            {
                FragColor = texture(u_Textures[textureIndex], TexCoord) * Color;
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
    };

    void Shader::Bind()
    {
        glUseProgram(m_ShaderProgram);
    }

    void Shader::SetMat4Uniform(glm::mat4 matrix)
    {
        GLint location = glGetUniformLocation(m_ShaderProgram, "u_Transform");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
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
            glGetProgramInfoLog(m_ShaderProgram, 512, 0, infoLog);
            spdlog::warn("InfoLog: {}", infoLog);
        }
    }
}
