#include "Rays.h"

// Field Of View
const int FOV = 75;
// Max distance of drawing (in blocks)
const int maxDistance = 8;


float shortestDistance(float x_1, float y_1, float x_2, float y_2)
{
    return (sqrt(pow(x_2 - x_1, 2) + pow(y_2 - y_1, 2)));
}


void drawingRays(float* playerX, float* playerY, float* playerAngle)
{
    int ray = 0;
    int levelX = 0, levelY = 0;
    int levelPosition = 0, depthOfField = 0;

    float rayX = 0, rayY = 0;
    float xOffset = 0, yOffset = 0;
    float distanceToObject = 1;

    float rayAngle = *playerAngle - (FOV / 2) * DEGREE;

    if (rayAngle < 0)
        rayAngle += 2 * M_PI;
    if (rayAngle > 2 * M_PI)
        rayAngle -= 2 * M_PI;

    for (ray = 0; ray < FOV; ray++)
    {
        int horizontalLevelTexture = 0, verticalLevelTexture = 0;

        // HORIZONTAL LINES----------------------------------------------------------------------------------
        float distanceHorizontal = INT_MAX;
        float horizontalX = *playerX;
        float horizontalY = *playerY;

        depthOfField = 0;
        float arcTan = -1 / tan(rayAngle);

        // Check if the player is looking up
        if (rayAngle > M_PI)
        {
            rayY = int(*playerY / 64) * 64 - 0.0001;
            rayX = (*playerY - rayY) * arcTan + *playerX;
            yOffset = -64;
            xOffset = -yOffset * arcTan;
        }
        // Check if the player is looking down
        if (rayAngle < M_PI)
        {
            rayY = int(*playerY / 64) * 64 + 64;
            rayX = (*playerY - rayY) * arcTan + *playerX;
            yOffset = 64;
            xOffset = -yOffset * arcTan;
        }
        // Check if the player is looking aside
        if (rayAngle == M_PI || rayAngle == 0)
        {
            rayX = *playerX;
            rayY = *playerY;
            depthOfField = maxDistance;
        }

        while (depthOfField < maxDistance)
        {
            levelX = int(rayX / 64);
            levelY = int(rayY / 64);
            levelPosition = levelY * LEVEL_WIDTH + levelX;

            // if ray hitted a horizontal wall...
            if (levelPosition > 0 && levelPosition < (LEVEL_WIDTH * LEVEL_HEIGHT) && level[levelPosition] > 0)
            {
                horizontalLevelTexture = level[levelPosition];
                depthOfField = maxDistance;
                horizontalX = rayX;
                horizontalY = rayY;
                distanceHorizontal = shortestDistance(*playerX, *playerY, horizontalX, horizontalY);
            }
            else    // if ray didn't hit a horizontal wall
            {
                rayX += xOffset;
                rayY += yOffset;
                depthOfField += 1;
            }
        }

        // VERTICAL LINES--------------------------------------------------------------------------------------
        float distanceVertical = INT_MAX;
        float verticalX = *playerX;
        float verticalY = *playerY;

        depthOfField = 0;
        float negativeTan = -tan(rayAngle);

        // Check if the player is looking left
        if (rayAngle > (M_PI / 2) && rayAngle < (3 * M_PI / 2))
        {
            rayX = int(*playerX / 64) * 64 - 0.0001;
            rayY = (*playerX - rayX) * negativeTan + *playerY;
            xOffset = -64;
            yOffset = -xOffset * negativeTan;
        }
        // Check if the player is looking right
        if (rayAngle < (M_PI / 2) || rayAngle >(3 * M_PI / 2))
        {
            rayX = int(*playerX / 64) * 64 + 64;
            rayY = (*playerX - rayX) * negativeTan + *playerY;
            xOffset = 64;
            yOffset = -xOffset * negativeTan;
        }
        // Check if the player is looking up or down
        if (rayAngle == (M_PI / 2) || rayAngle == (3 * M_PI / 2))
        {
            rayX = *playerX;
            rayY = *playerY;
            depthOfField = maxDistance;
        }

        while (depthOfField < maxDistance)
        {
            levelX = int(rayX / 64);
            levelY = int(rayY / 64);
            levelPosition = levelY * LEVEL_WIDTH + levelX;
            // if ray hitted a vertical wall...
            if (levelPosition > 0 && levelPosition < (LEVEL_WIDTH * LEVEL_HEIGHT) && level[levelPosition] > 0)
            {
                verticalLevelTexture = level[levelPosition];
                depthOfField = maxDistance;
                verticalX = rayX;
                verticalY = rayY;
                distanceVertical = shortestDistance(*playerX, *playerY, verticalX, verticalY);
            }
            else    // if ray didn't hit a vertical wall
            {
                rayX += xOffset;
                rayY += yOffset;
                depthOfField += 1;
            }
        }

        // DISTANCE--------------------------------
        float shade = 1;
        // Check if a ray hitting a horizontal line
        if (distanceHorizontal < distanceVertical)
        {
            rayX = horizontalX;
            rayY = horizontalY;
            distanceToObject = distanceHorizontal;

            switch (horizontalLevelTexture)
            {
            case Walls::Wall:
                glColor3f(0, 0, 0.8);
                break;
            case Walls::Door:
                glColor3f(0, 0.8, 0);
                break;
            default:
                break;
            }
        }
        // Check if a ray hitting a vertical line
        if (distanceHorizontal > distanceVertical)
        {
            rayX = verticalX;
            rayY = verticalY;
            distanceToObject = distanceVertical;
            shade = 0.5;
            horizontalLevelTexture = verticalLevelTexture;

            switch (verticalLevelTexture)
            {
            case Walls::Wall:
                glColor3f(0, 0, 0.8 * shade);
                break;
            case Walls::Door:
                glColor3f(0, 0.8 * shade, 0);
                break;
            default:
                break;
            }
        }

        // Drawing a ray
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2i(*playerX, *playerY);
        glVertex2i(rayX, rayY);
        glEnd();

        // Next ray
        rayAngle += DEGREE;
        if (rayAngle < 0)
            rayAngle += 2 * M_PI;
        if (rayAngle > 2 * M_PI)
            rayAngle -= 2 * M_PI;
    }
}

void drawing3D(float* playerX, float* playerY, float* playerAngle)
{
    int ray = 0;
    int levelX = 0, levelY = 0;
    int levelPosition = 0, depthOfField = 0;

    float rayX = 0, rayY = 0;
    float xOffset = 0, yOffset = 0;
    float distanceToObject = 1;

    float rayAngle = *playerAngle - (FOV / 2) * DEGREE;

    if (rayAngle < 0)
        rayAngle += 2 * M_PI;
    if (rayAngle > 2 * M_PI)
        rayAngle -= 2 * M_PI;

    for (ray = 0; ray < FOV; ray++)
    {
        int horizontalLevelTexture = 0, verticalLevelTexture = 0;

        // HORIZONTAL LINES----------------------------------------------------------------------------------
        float distanceHorizontal = INT_MAX;
        float horizontalX = *playerX;
        float horizontalY = *playerY;

        depthOfField = 0;
        float arcTan = -1 / tan(rayAngle);

        // Check if the player is looking up
        if (rayAngle > M_PI)
        {
            rayY = int(*playerY / 64) * 64 - 0.0001;
            rayX = (*playerY - rayY) * arcTan + *playerX;
            yOffset = -64;
            xOffset = -yOffset * arcTan;
        }
        // Check if the player is looking down
        if (rayAngle < M_PI)
        {
            rayY = int(*playerY / 64) * 64 + 64;
            rayX = (*playerY - rayY) * arcTan + *playerX;
            yOffset = 64;
            xOffset = -yOffset * arcTan;
        }
        // Check if the player is looking aside
        if (rayAngle == M_PI || rayAngle == 0)
        {
            rayX = *playerX;
            rayY = *playerY;
            depthOfField = maxDistance;
        }

        while (depthOfField < maxDistance)
        {
            levelX = int(rayX / 64);
            levelY = int(rayY / 64);
            levelPosition = levelY * LEVEL_WIDTH + levelX;

            // if ray hitted a horizontal wall...
            if (levelPosition > 0 && levelPosition < (LEVEL_WIDTH * LEVEL_HEIGHT) && level[levelPosition] > 0)
            {
                horizontalLevelTexture = level[levelPosition];
                depthOfField = maxDistance;
                horizontalX = rayX;
                horizontalY = rayY;
                distanceHorizontal = shortestDistance(*playerX, *playerY, horizontalX, horizontalY);
            }
            else    // if ray didn't hit a horizontal wall
            {
                rayX += xOffset;
                rayY += yOffset;
                depthOfField += 1;
            }
        }

        // VERTICAL LINES--------------------------------------------------------------------------------------
        float distanceVertical = INT_MAX;
        float verticalX = *playerX;
        float verticalY = *playerY;

        depthOfField = 0;
        float negativeTan = -tan(rayAngle);

        // Check if the player is looking left
        if (rayAngle > (M_PI / 2) && rayAngle < (3 * M_PI / 2))
        {
            rayX = int(*playerX / 64) * 64 - 0.0001;
            rayY = (*playerX - rayX) * negativeTan + *playerY;
            xOffset = -64;
            yOffset = -xOffset * negativeTan;
        }
        // Check if the player is looking right
        if (rayAngle < (M_PI / 2) || rayAngle >(3 * M_PI / 2))
        {
            rayX = int(*playerX / 64) * 64 + 64;
            rayY = (*playerX - rayX) * negativeTan + *playerY;
            xOffset = 64;
            yOffset = -xOffset * negativeTan;
        }
        // Check if the player is looking up or down
        if (rayAngle == (M_PI / 2) || rayAngle == (3 * M_PI / 2))
        {
            rayX = *playerX;
            rayY = *playerY;
            depthOfField = maxDistance;
        }

        while (depthOfField < maxDistance)
        {
            levelX = int(rayX / 64);
            levelY = int(rayY / 64);
            levelPosition = levelY * LEVEL_WIDTH + levelX;
            // if ray hitted a vertical wall...
            if (levelPosition > 0 && levelPosition < (LEVEL_WIDTH * LEVEL_HEIGHT) && level[levelPosition] > 0)
            {
                verticalLevelTexture = level[levelPosition];
                depthOfField = maxDistance;
                verticalX = rayX;
                verticalY = rayY;
                distanceVertical = shortestDistance(*playerX, *playerY, verticalX, verticalY);
            }
            else    // if ray didn't hit a vertical wall
            {
                rayX += xOffset;
                rayY += yOffset;
                depthOfField += 1;
            }
        }

        // DISTANCE--------------------------------
        float shade = 1;
        // Check if a ray hitting a horizontal line
        if (distanceHorizontal < distanceVertical)
        {
            rayX = horizontalX;
            rayY = horizontalY;
            distanceToObject = distanceHorizontal;

            switch (horizontalLevelTexture)
            {
            case Walls::Wall:
                glColor3f(0, 0, 0.8);
                break;
            case Walls::Door:
                glColor3f(0, 0.8, 0);
                break;
            default:
                break;
            }
        }
        // Check if a ray hitting a vertical line
        if (distanceHorizontal > distanceVertical)
        {
            rayX = verticalX;
            rayY = verticalY;
            distanceToObject = distanceVertical;
            shade = 0.5;
            horizontalLevelTexture = verticalLevelTexture;

            switch (verticalLevelTexture)
            {
            case Walls::Wall:
                glColor3f(0, 0, 0.8 * shade);
                break;
            case Walls::Door:
                glColor3f(0, 0.8 * shade, 0);
                break;
            default:
                break;
            }
        }

        // DRAW WALLS----------------------------------------------
        // fisheye fix
        float cameraAngle = *playerAngle - rayAngle;
        if (cameraAngle < 0)
            cameraAngle += 2 * M_PI;
        if (cameraAngle > 2 * M_PI)
            cameraAngle -= 2 * M_PI;
        distanceToObject = cos(cameraAngle) * distanceToObject;

        float lineVertical = (LEVEL_SIZE * WALL_HEIGHT_LIMIT) / distanceToObject;
        // setting a line height and the limit
        if (lineVertical > WALL_HEIGHT_LIMIT)
        {
            lineVertical = WALL_HEIGHT_LIMIT;
        }
        // line offset
        float lineOffset = WALL_HEIGHT_LIMIT / 2 - lineVertical / 2;

        for (int y = 0; y < lineVertical; y++)
        {
            glPointSize(8);
            glBegin(GL_POINTS);
            glVertex2i(ray * 8 + 530, y + lineOffset);
            glEnd();
        }

        // Next ray
        rayAngle += DEGREE;
        if (rayAngle < 0)
            rayAngle += 2 * M_PI;
        if (rayAngle > 2 * M_PI)
            rayAngle -= 2 * M_PI;
    }
}