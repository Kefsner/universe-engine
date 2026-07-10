#include <iostream>
#include <cassert>

#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

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