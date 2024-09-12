#pragma once
#include <Windows.h>
#include <gl/GLU.h>
#include <math.h>
#include "DrawingPlayer.h"
#include "Buttons.h"
#include "Level.h"
#include "Rays.h"

// COLORS
#define FLOOR_COLOR_R 0.4
#define FLOOR_COLOR_G 0.4
#define FLOOR_COLOR_B 0.4
#define WALL_COLOR_R 0
#define WALL_COLOR_G 0
#define WALL_COLOR_B 1

// WINDOW'S SIZE
#define WIDTH 1024
#define HEIGHT 512

// Defining basic parameters
void initialization();

// Function to render a window of topdown vision via OpenGL
int open_topdown_window();

// Function to render a window of 3D vision via OpenGL
int open_3D_window();