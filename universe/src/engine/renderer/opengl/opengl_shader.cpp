#include "pch.hpp"
#include "engine/renderer/opengl/opengl_shader.hpp"
#include <glad/glad.h>

namespace Universe {

    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        source = fragmentSrc.c_str(); // Reset the source to the fragment shader source
        glShaderSource(fragmentShader, 1, &source, 0);
        glCompileShader(fragmentShader);

        m_RendererID = glCreateProgram();
        GLuint program = m_RendererID;
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_RendererID);
    }
}