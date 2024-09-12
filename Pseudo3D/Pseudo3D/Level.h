#pragma once
#include <GLFW/glfw3.h>

#define LEVEL_WIDTH 8
#define LEVEL_HEIGHT 8
#define LEVEL_SIZE 64

struct Walls
{
public:
    const static int Empty = 0;
    const static int Wall = 1;
    const static int Door = 2;
};

extern int level[];

void drawingMap(float wallR, float wallG, float wallB,
				float floorR, float floorG, float floorB);