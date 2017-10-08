#include <GL/glut.h> 
#include <stdlib.h> 

#include <algorithm> 
#include <math.h> 
#include"GraphicsLibrary.h"

using namespace std;

// TODO more univesal
void GL::SetPixel(int x, int y, float size)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void GL::DrawVertice(int x, int y)
{
	GL::SetPixel(x, y, 6);
}
void GL::DrawHighlitVertice(int x, int y)
{

	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(6);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
vector<GL::Point> GL::Line(int x1, int y1, int x2, int y2)
{
	vector<GL::Point> edge;
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
			edge.push_back(GL::Point(y, x));
			//GL::SetPixel(y, x);
		}
		else
		{
			edge.push_back(GL::Point(x, y));
			//GL::SetPixel(x, y);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
	for each (GL::Point p in edge)
	{
		GL::SetPixel(p.x, p.y);
	}
	return edge;
}
void GL::Drawline(GL::Point p1, GL::Point p2)
{
	GL::Line(p1.x, p1.y, p2.x, p2.y);
}

void GL::DrawEdge(GL::Polygon*  polygon)
{
	Point p1 = polygon->GetPoint(polygon->VerticesCount() - 2);
	Point p2 = polygon->GetPoint(polygon->VerticesCount() - 1);
	polygon->AddEdge(GL::Line(p1.x, p1.y, p2.x, p2.y));
}
