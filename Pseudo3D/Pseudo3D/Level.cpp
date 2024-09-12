#include "Level.h"

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

void drawingMap(float wallR, float wallG, float wallB,
                float floorR, float floorG, float floorB)
{
    int x, y, x0, y0;
    bool isWall;

    for (y = 0; y < LEVEL_HEIGHT; y++)
    {
        for (x = 0; x < LEVEL_WIDTH; x++)
        {
            (level[y * LEVEL_WIDTH + x] > 0) ?
                (glColor3f(wallR, wallG, wallB), isWall = true) :
                (glColor3f(floorR, floorG, floorB), isWall = false);

            //switch (level[y * LEVEL_WIDTH + x])
            //{
            //case Walls::Empty:
            //    glColor3f(floorR, floorG, floorB);
            //    isWall = false;
            //case Walls::Wall:
            //    glColor3f(wallR, wallG, wallB);
            //    isWall = true;
            //case Walls::Door:
            //    glColor3f(0, 0.8, 0);
            //    isWall = true;
            //default:
            //    isWall = false;
            //    break;
            //}

            x0 = x * LEVEL_SIZE;
            y0 = y * LEVEL_SIZE;

            glBegin(GL_QUADS);

            if (isWall)
            {
                glVertex2i(x0 + 1, y0 + 1);
                glVertex2i(x0 + 1, y0 + LEVEL_SIZE - 1);
                glVertex2i(x0 + LEVEL_SIZE - 1, y0 + LEVEL_SIZE - 1);
                glVertex2i(x0 + LEVEL_SIZE - 1, y0 + 1);
            }
            else
            {
                glVertex2i(x0, y0);
                glVertex2i(x0, y0 + LEVEL_SIZE);
                glVertex2i(x0 + LEVEL_SIZE, y0 + LEVEL_SIZE);
                glVertex2i(x0 + LEVEL_SIZE, y0);
            }

            glEnd();
        }
    }
}
