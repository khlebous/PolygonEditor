#include <GL/glut.h> 
#include <stdlib.h> 

#include <algorithm> 
#include <math.h> 
#include"GraphicsLibrary.h"

using namespace std;


void Line(int x1, int y1, int x2, int y2)
{
	// Bresenham's line algorithm
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	float dx = x2 - x1;
	float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	int maxX = (int)x2;

	for (int x = (int)x1; x < maxX; x++)
	{
		if (steep)
		{
			MySetPixel(y, x);
		}
		else
		{
			MySetPixel(x, y);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}
void Drawline(GL::Point p1, GL::Point p2)
{
	Line(p1.x, p1.y, p2.x, p2.y);
}

void MySetPixel(int x, int y)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}


