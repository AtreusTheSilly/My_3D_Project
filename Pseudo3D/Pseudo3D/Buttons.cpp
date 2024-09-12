#include "Buttons.h"
#include "Level.h"

int FPS_UpDown_Multiplyer = 512;
int FPS_LeftRight_Multiplyer = 2;

void buttonsHandler(GLFWwindow* window,
                    float* playerX, float* playerY,
                    float* playerDeltaX, float* playerDeltaY,
                    float* playerAngle,
                    float* fps)
{
    int xOffset = 0, yOffset = 0;
    (*playerDeltaX < 0) ? (xOffset = -10) : (xOffset = 10);
    (*playerDeltaY < 0) ? (yOffset = -10) : (yOffset = 10);

    int partialPlayerX = *playerX / 64;
    int partialPlayerY = *playerY / 64;
    int partialPlayerX_plus_xOffset = (*playerX + xOffset) / 64;
    int partialPlayerY_plus_yOffset = (*playerY + yOffset) / 64;
    int partialPlayerX_minus_xOffset = (*playerX - xOffset) / 64;
    int partialPlayerY_minus_yOffset = (*playerY - yOffset) / 64;

    // Move up (forward)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (level[partialPlayerY * LEVEL_WIDTH + partialPlayerX_plus_xOffset] == 0)
            *playerX += *playerDeltaX * FPS_UpDown_Multiplyer * *fps;
        if (level[partialPlayerY_plus_yOffset * LEVEL_WIDTH + partialPlayerX] == 0)
            *playerY += *playerDeltaY * FPS_UpDown_Multiplyer * *fps;
    }
    // Move left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        *playerAngle -= FPS_LeftRight_Multiplyer * *fps;

        if (*playerAngle < 0)
            *playerAngle = 2 * M_PI;

        *playerDeltaX = cos(*playerAngle) / 6;
        *playerDeltaY = sin(*playerAngle) / 6;
    }
    // Move down (backward)
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (level[partialPlayerY * LEVEL_WIDTH + partialPlayerX_minus_xOffset] == 0)
            *playerX -= *playerDeltaX * FPS_UpDown_Multiplyer * *fps;
        if (level[partialPlayerY_minus_yOffset * LEVEL_WIDTH + partialPlayerX] == 0)
            *playerY -= *playerDeltaY * FPS_UpDown_Multiplyer * *fps;
    }
    // Move right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        *playerAngle += FPS_LeftRight_Multiplyer * *fps;

        if (*playerAngle > 2 * M_PI)
            *playerAngle = 0;

        *playerDeltaX = cos(*playerAngle) / 6;
        *playerDeltaY = sin(*playerAngle) / 6;
    }
    // Open doors
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        (*playerDeltaX < 0) ? (xOffset = -20) : (xOffset = 20);
        (*playerDeltaY < 0) ? (yOffset = -20) : (yOffset = 20);

        partialPlayerX = *playerX / 64;
        partialPlayerY = *playerY / 64;
        partialPlayerX_plus_xOffset = (*playerX + xOffset) / 64;
        partialPlayerY_plus_yOffset = (*playerY + yOffset) / 64;

        if (level[partialPlayerY_plus_yOffset * LEVEL_WIDTH + partialPlayerX_plus_xOffset] == Walls::Door)
        {
            level[partialPlayerY_plus_yOffset * LEVEL_WIDTH + partialPlayerX_plus_xOffset] = Walls::Empty;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}