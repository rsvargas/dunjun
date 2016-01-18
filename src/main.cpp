#include <Dunjun/Common.hpp>
#include <Dunjun/ShaderProgram.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <string>

GLOBAL const int g_windowWidth  = 854;
GLOBAL const int g_windowHeight = 480;




INTERNAL void glfwHints()
{
    glfwWindowHint(GLFW_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_VERSION_MINOR, 1);
}

int main(int argc, char** argv)
{
    GLFWwindow* window;

    if (!glfwInit())
        return EXIT_FAILURE;

    glfwHints();
    window = glfwCreateWindow(
        g_windowWidth, g_windowHeight, "Dunjun", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    float vertices[] = {
    //      x,     y,     r,    g,   b
        +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, //vertex 0
        -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, //vertex 1
        +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, //vertex 2
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, //vertex 3

    };

    GLuint vbo;  //vertex buffer object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Dunjun::ShaderProgram shaderProgram;
    shaderProgram.attachShaderFromFile(Dunjun::ShaderType::Vertex, "data/shaders/default.vert.glsl");
    shaderProgram.attachShaderFromFile(Dunjun::ShaderType::Fragment, "data/shaders/default.frag.glsl");

    shaderProgram.bindAttribLocation(0, "vertPosition");
    shaderProgram.bindAttribLocation(1, "vertColor");

    shaderProgram.link();
    shaderProgram.use();
    
    bool running    = true;
    bool fullscreen = false;
    while (running)
    {
        glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw things
        {
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const GLvoid*)(2*sizeof(float)));

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwWindowShouldClose(window) ||
            glfwGetKey(window, GLFW_KEY_ESCAPE))
            running = false;

        if (glfwGetKey(window, GLFW_KEY_F11))
        {
            fullscreen = !fullscreen;

            GLFWwindow* newWindow;
            glfwHints();
                if (fullscreen)
            {
                //int count;
                //const GLFWvidmode* modes =
                //    glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
                //for (int modeIndex = 0; modeIndex < count; ++modeIndex)
                //{
                //    std::cout << modeIndex << " - " << modes[modeIndex].width
                //              << "x" << modes[modeIndex].height << std::endl;
                //}
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