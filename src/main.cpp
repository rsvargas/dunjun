#include <Dunjun/Common.hpp>

#include <GLFW/glfw3.h>

#include <iostream>

GLOBAL const int g_windowWidth  = 854;
GLOBAL const int g_windowHeight = 480;

int main(int argc, char** argv)
{
    GLFWwindow* window;

    if (!glfwInit())
        return EXIT_FAILURE;

    window = glfwCreateWindow(
        g_windowWidth, g_windowHeight, "Dunjun", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    bool running    = true;
    bool fullscreen = false;
    while (running)
    {
        glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwWindowShouldClose(window) ||
            glfwGetKey(window, GLFW_KEY_ESCAPE))
            running = false;

        if (glfwGetKey(window, GLFW_KEY_F11))
        {
            fullscreen = !fullscreen;

            GLFWwindow* newWindow;
            if (fullscreen)
            {
                int count;
                const GLFWvidmode* modes =
                    glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
                for (int modeIndex = 0; modeIndex < count; ++modeIndex)
                {
                    std::cout << modeIndex << " - " << modes[modeIndex].width
                              << "x" << modes[modeIndex].height << std::endl;
                }
                newWindow = glfwCreateWindow(
                    1920, 1080, "Dunjun", glfwGetPrimaryMonitor(), window);
            }
            else
            {
                newWindow = glfwCreateWindow(
                    g_windowWidth, g_windowHeight, "Dunjun", nullptr, window);
            }
            glfwDestroyWindow(window);
            window = newWindow;
            glfwMakeContextCurrent(window);
        }
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}