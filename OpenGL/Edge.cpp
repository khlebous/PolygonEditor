#include "Edge.h"
#include <algorithm> 
#include <math.h> 

GL::Edge::Edge()
{
	points = vector<GL::Point>();
}
GL::Edge::Edge(GL::Vertice v1, GL::Vertice v2)
{
	int x1 = v1.GetX();
	int y1 = v1.GetY();
	int x2 = v2.GetX();
	int y2 = v2.GetY();

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
			edge.push_back(GL::Point(y, x));
		else
			edge.push_back(GL::Point(x, y));

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
	points = edge;
}
GL::Edge::~Edge()
{
	points.clear();
}

void GL::Edge::Draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (GL::Point& p : points)
		glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
}
void GL::Edge::Highlight()
{
	glColor3f(1.0f, 0.0f, 1.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (GL::Point& p : points)
		glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
}
void GL::Edge::Unhighlight()
{
	Draw();
}

bool GL::Edge::IsPointNear(int x, int y, int maxDistance)
{
	bool val = false;
	for each (GL::Point p in points)
		if ((abs(p.x - x) < maxDistance) && (abs(p.y - y) < maxDistance))
		{
			val = true;
			break;
		}
	return val;
}

bool GL::Edge::operator==(Edge & e) const
{
	vector<GL::Point> p = e.GetPoints();
	if (Length() == 0 || p.size() == 0)
		return false;
	else if ((points[0] == p[0]) && (points[Length()-1] == p[p.size()-1]))
		return true;
	else
		return false;
	/*if (p1.size() != p2.size())
	return false;
	else
	{
	for (std::vector<GL::Point>::iterator it1 = p1.begin(),
	it2 = p2.begin(); it1 != p1.end(); ++it1, ++it2)
	{
	if (*it1 != *it2)
	return false;
	}
	return true;
	}*/
}

bool GL::Edge::operator!=(Edge & e) const
{
	vector<GL::Point> p = e.GetPoints();
	if (Length() == 0 || p.size() == 0 ||(points[0] != p[0]) || (points[Length()-1] != p[p.size()-1]))
		return true;
	else
		return false;
}


