#include "Polygon.h"

GL::Polygon::Polygon()
{
	vertices = vector<Point>();
}

GL::Polygon::~Polygon()
{
	vertices.clear();
}

void GL::Polygon::AddVertice(int x, int y)
{
	vertices.push_back(GL::Point(x,y));
}

void GL::Polygon::AddVertice(GL::Point p)
{
	vertices.push_back(GL::Point(p));
}

GL::Point GL::Polygon::GetPoint(int index)
{
	return vertices[index];
}
