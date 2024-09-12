#pragma once

#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include "cmath"
#include "Level.h"

// One degree in radians
#define DEGREE M_PI / 180
#define WALL_HEIGHT_LIMIT 320

extern float rayAngle;

// Function to calculate the shortest distance to a block
float shortestDistance(float x_1, float y_1, float x_2, float y_2);

// Function to draw a top-down vision of the level
void drawingRays(float* playerX, float* playerY, float* playerAngle);

// Function to draw a 3D vision of the level
void drawing3D(float* playerX, float* playerY, float* playerAngle);