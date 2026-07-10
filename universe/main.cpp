#include <iostream>
#include <cassert>

#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        spdlog::info("Severity Notificaion: {}", message);
        break;
    case GL_DEBUG_SEVERITY_LOW:
        spdlog::warn("Severity Low: {}", message);
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        spdlog::warn("Severity Medium: {}", message);
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        spdlog::error("Severity High: {}", message);
        assert(false);
        break;
    default:
        break;
    }
};

int main()
{
    spdlog::info("Welcome to spdlog!");
    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        spdlog::info("Failed to initialize GLFW.");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    struct WindowProps
    {
        int Height;
        int Width;
        const char* Title;
    };

    WindowProps windowProps{
        .Height = 1920,
        .Width = 1080,
        .Title = "Hello, Universe!"
    };
    
    window = glfwCreateWindow(windowProps.Height, windowProps.Width, windowProps.Title, NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        spdlog::info("Failed to create a window.");
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        spdlog::info("Failed to initialize GLAD.");
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glViewport(0, 0, windowProps.Width, windowProps.Height);

    /* Get GLFW version */
    int glfwMajor;
    int glfwMinor;
    glfwGetVersion(&glfwMajor, &glfwMinor, nullptr);

    spdlog::info("GLFW Major {}", glfwMajor); // 3
    spdlog::info("GLFW Minor {}", glfwMinor); // 4

    /* Get OpenGL version */
    int glMajor;
    int glMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
    glGetIntegerv(GL_MINOR_VERSION, &glMinor);

    spdlog::info("OpenGL Major {}", glMajor);
    spdlog::info("OpenGL Minor {}", glMinor);
    
    GLint profile = 0;
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);

    spdlog::info("Profile {}", profile);

    if (profile == GL_CONTEXT_CORE_PROFILE_BIT)
        spdlog::info("Core profile");

    if (profile == GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
        spdlog::info("Compatibility profile");

    spdlog::info("OpenGL Core Profile {}", GL_CONTEXT_CORE_PROFILE_BIT);
    spdlog::info("OpenGL Compat Profile {}", GL_CONTEXT_COMPATIBILITY_PROFILE_BIT);

    int glfwProfile = glfwGetWindowAttrib(window, GLFW_OPENGL_PROFILE);
    spdlog::info("GLFW profile {}", glfwProfile);

    if (glfwProfile == GLFW_OPENGL_CORE_PROFILE)
        spdlog::info("GLFW - Core profile");
    
    if (glfwProfile == GLFW_OPENGL_COMPAT_PROFILE)
        spdlog::info("GLFW - Compat profile");

    int glfwClientAPI = glfwGetWindowAttrib(window, GLFW_CLIENT_API);
    spdlog::info("GLFW Client API {}", glfwClientAPI);

    switch (glfwGetWindowAttrib(window, GLFW_CONTEXT_DEBUG))
    {
    case GLFW_TRUE:
        spdlog::info("TRUEZAO");
        break;
    
    case GLFW_FALSE:
        spdlog::info("FALSAO");
        break;

    default:
        assert(false);
        break;
    }

    switch (glfwClientAPI)
    {
    case GLFW_OPENGL_API:
        spdlog::info("GLFW OpenGL API");
        break;
    
    case GLFW_OPENGL_ES_API:
        spdlog::info("GLFW OpenGL ES API");
        break;

    case GLFW_NO_API:
        spdlog::info("GLFW No API");
        break;

    default:
        assert(false);
        break;
    }

    assert(glfwGetWindowAttrib(window, GLFW_CONTEXT_CREATION_API) == GLFW_NATIVE_CONTEXT_API);

    // Graphics
    /* Vertices Coordinates */
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    int numVertices = 2;
    int glError = 0;

    glDebugMessageCallback(debugCallback, 0);

    GLuint vertexBuffer;
    glCreateBuffers(1, &vertexBuffer);

    GLsizeiptr vertexBufferSize;
    vertexBufferSize = 9*sizeof(float);

    glNamedBufferData(vertexBuffer, vertexBufferSize, &vertices, GL_STATIC_DRAW);

    // Shaders
    const char* vertexShaderSrc = R"(
        #version 460 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";

    // Shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);

    // Shader compilation issues
    int successVertex;
    char infoLogVertex[1024];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);

    if (!successVertex)
    {
        spdlog::info("Failed to compile vertex shader");
        glGetShaderInfoLog(vertexShader, 1024, 0, infoLogVertex);
        spdlog::info("InfoLog vertex {}", infoLogVertex);
    }

    const char* fragmentShaderSrc = R"(
        #version 460 core

        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        }
    )";
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);

    int successFragment;
    char infoLogFragment[1024];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);

    if (!successFragment)
    {
        spdlog::info("Failed to compile fragment shader");
        glGetShaderInfoLog(fragmentShader, 1024, 0, infoLogFragment);
        spdlog::info("InfoLog fragment {}", infoLogFragment);
    }

    // Shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int successProgram;
    char infoLogProgram[1024];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successProgram);

    if (!successProgram)
    {
        spdlog::info("Failed to link shader program");
        glGetProgramInfoLog(shaderProgram, 1024, 0, infoLogProgram);
        spdlog::info("InfoLog shader program {}", infoLogProgram);
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}