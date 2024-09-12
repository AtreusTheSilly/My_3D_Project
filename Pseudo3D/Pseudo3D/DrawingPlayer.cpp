#include "DrawingPlayer.h"

void drawingPlayer(float* playerX, float* playerY, float* playerDeltaX, float* playerDeltaY)
{
	// DRAWING PLAYER -------------
	// Player's size
	glPointSize(8);
	// Player's color
	glColor3f(1, 0, 0);

	glBegin(GL_POINTS);
	glVertex2i(*playerX, *playerY);
	glEnd();


	// DRAWING PLAYER'S VIEW --------------------------------------------------
	glLineWidth(3);

	glBegin(GL_LINES);
	glVertex2i(*playerX, *playerY);
	glVertex2i(*playerX + *playerDeltaX * 150, *playerY + *playerDeltaY * 150);
	glEnd();
	//drawingRays();
}
