#include "pch.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "universe/renderer/opengl/opengl_shader.hpp"

namespace Universe
{
    OpenGLShader::OpenGLShader(const char* name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name)
    {
        const char* vertexSrcCStr = vertexSrc.c_str();
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSrcCStr, nullptr);
        glCompileShader(vertexShader);
        CheckShaderCompilation(vertexShader, "VERTEX");

        const char* fragmentSrcCStr = fragmentSrc.c_str();
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSrcCStr, nullptr);
        glCompileShader(fragmentShader);
        CheckShaderCompilation(fragmentShader, "FRAGMENT");

        m_ShaderID = glCreateProgram();
        glAttachShader(m_ShaderID, vertexShader);
        glAttachShader(m_ShaderID, fragmentShader);
        glLinkProgram(m_ShaderID);
        CheckProgramLinking(m_ShaderID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_ShaderID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_ShaderID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::CheckShaderCompilation(GLuint shader, const std::string& type)
    {
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            UE_CORE_ERROR("Shader compilation error: {0} shader\n{1}", type, infoLog);
        }
    }

    void OpenGLShader::CheckProgramLinking(GLuint program)
    {
        int success;
        char infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            UE_CORE_ERROR("Program linking error: {0}", infoLog);
        }
    }

    void OpenGLShader::SetUniformInt(const char* name, int value)
    {
        GLint location = glGetUniformLocation(m_ShaderID, name);
        #if UE_DEBUG
        if (location == -1)
            UE_CORE_WARN("Uniform {0} not found in shader {1}", name, m_Name);
        #endif
        glUniform1i(location, value);
    }

    void OpenGLShader::SetUniformFloat4(const char* name, const glm::vec4& vector)
    {
        GLint location = glGetUniformLocation(m_ShaderID, name);
        #if UE_DEBUG
        if (location == -1)
            UE_CORE_WARN("Uniform {0} not found in shader {1}", name, m_Name);
        #endif
        glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
    }

    void OpenGLShader::SetUniformMat4(const char* name, const glm::mat4& matrix)
    {
        GLint location = glGetUniformLocation(m_ShaderID, name);
        #if UE_DEBUG
        if (location == -1)
            UE_CORE_WARN("Uniform {0} not found in shader {1}", name, m_Name);
        #endif
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}