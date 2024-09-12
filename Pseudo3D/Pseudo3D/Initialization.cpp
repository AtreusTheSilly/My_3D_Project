#include "Initialization.h"

// Player's coordinates
float _playerX, _playerY;
float _playerDeltaX, _playerDeltaY;
float _playerAngle;

float frame1, frame2, fps;

void initialization()
{
    glClearColor(FLOOR_COLOR_R, FLOOR_COLOR_G, FLOOR_COLOR_B, 0);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    _playerX = 200;
    _playerY = 200;
}


int open_topdown_window()
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(1024, 512, "Pseudo3D", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    initialization();

    glfwSetWindowPos(window, 200, 200);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        frame2 = glfwGetTime();
        fps = frame2 - frame1;
        frame1 = glfwGetTime();

        drawingMap(WALL_COLOR_R, WALL_COLOR_G, WALL_COLOR_B, FLOOR_COLOR_R, FLOOR_COLOR_G, FLOOR_COLOR_B);
        drawingPlayer(&_playerX, &_playerY, &_playerDeltaX, &_playerDeltaY);
        drawingRays(&_playerX, &_playerY, &_playerAngle);

        drawing3D(&_playerX, &_playerY, &_playerAngle);

        buttonsHandler(window, &_playerX, &_playerY, &_playerDeltaX, &_playerDeltaY, &_playerAngle, &fps);

        // Swap front and back buffers
        glfwSwapBuffers(window);


        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

int open_3D_window()
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(1024, 512, "Pseudo3D", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    initialization();

    glfwSetWindowPos(window, 200, 200);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        frame2 = glfwGetTime();
        fps = frame2 - frame1;
        frame1 = glfwGetTime();

        drawing3D(&_playerX, &_playerY, &_playerAngle);

        buttonsHandler(window, &_playerX, &_playerY, &_playerDeltaX, &_playerDeltaY, &_playerAngle, &fps);

        // Swap front and back buffers
        glfwSwapBuffers(window);


        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
