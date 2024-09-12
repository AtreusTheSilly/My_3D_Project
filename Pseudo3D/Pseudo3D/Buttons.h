#pragma once

#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <cmath>

extern int FPS_UpDown_Multiplyer;
extern int FPS_LeftRight_Multiplyer;

void buttonsHandler(GLFWwindow* window,
					float* playerX, float* playerY,
					float* playerDeltaX, float* playerDeltaY,
					float* playerAngle,
					float* fps);