#include "Level.h"

// Level map (8x8 grid) where 
// '0' is an empty space,
// '1' is a wall,
// '2' is a door
int level[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 1, 0, 0, 1,
    1, 0, 0, 0, 1, 0, 0, 1,
    1, 0, 1, 1, 1, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 2, 1, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};


// Function used for debugging to render the level map in 2D (top-down view)
// wallR, wallG, wallB — wall color
// floorR, floorG, floorB — floor color
void drawingMap(float wallR, float wallG, float wallB,
                float floorR, float floorG, float floorB)
{
    int x, y, x0, y0;
    bool isWall;

    // Iterate through each cell in the map
    for (y = 0; y < LEVEL_HEIGHT; y++)
    {
        for (x = 0; x < LEVEL_WIDTH; x++)
        {
            // Determine whether the current cell is an empty space or a wall and paint it
            (level[y * LEVEL_WIDTH + x] > 0) ?
                (glColor3f(wallR, wallG, wallB), isWall = true) :
                (glColor3f(floorR, floorG, floorB), isWall = false);

            // Calculate the top-left corner coordinates of the cell
            x0 = x * LEVEL_SIZE;
            y0 = y * LEVEL_SIZE;

            glBegin(GL_QUADS);

            if (isWall)
            {
                // Draw a slightly smaller quad for wall tiles
                glVertex2i(x0 + 1, y0 + 1);
                glVertex2i(x0 + 1, y0 + LEVEL_SIZE - 1);
                glVertex2i(x0 + LEVEL_SIZE - 1, y0 + LEVEL_SIZE - 1);
                glVertex2i(x0 + LEVEL_SIZE - 1, y0 + 1);
            }
            else
            {
                // Draw a full-sized quad for floor tiles
                glVertex2i(x0, y0);
                glVertex2i(x0, y0 + LEVEL_SIZE);
                glVertex2i(x0 + LEVEL_SIZE, y0 + LEVEL_SIZE);
                glVertex2i(x0 + LEVEL_SIZE, y0);
            }

            glEnd();
        }
    }
}
