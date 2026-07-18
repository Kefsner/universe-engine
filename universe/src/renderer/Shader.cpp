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

            uniform mat4 u_Transform;
            uniform mat4 u_Projection;
            uniform mat4 u_View;
            
            out vec4 Color;

            void main()
            {
                gl_Position = u_Projection * u_View * u_Transform * vec4(aPos, 1.0);
                Color = vec4(1.0);
            }
        )";

        const char* fragmentShaderSrc = R"(
            #version 460 core
            
            in vec4 Color;
            out vec4 FragColor;

            uniform sampler2D u_Textures[32];
            uniform int textureIndex;

            void main()
            {
                FragColor = texture(u_Textures[textureIndex], vec2(0.9, 0.5)) * Color;
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

    void Shader::SetMat4Uniform(glm::mat4 matrix, const char* name)
    {
        GLint location = glGetUniformLocation(m_ShaderProgram, name);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::SetVec2Uniform(glm::vec2 vector, const char* name)
    {
        GLint location = glGetUniformLocation(m_ShaderProgram, name);
        glUniform2f(location, vector[0], vector[1]);
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
