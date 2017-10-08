#include "Polygon.h"

GL::Polygon::Polygon()
{
	vertices = vector<GL::Point>();
	edges = vector<vector<GL::Point>>();
}

GL::Polygon::~Polygon()
{
	vertices.clear();
	for each (vector<GL::Point> v in edges)
		v.clear();
	edges.clear();
}

void GL::Polygon::AddVertice(int x, int y)
{
	vertices.push_back(GL::Point(x, y));
}

void GL::Polygon::AddVertice(GL::Point p)
{
	vertices.push_back(GL::Point(p));
}

void GL::Polygon::AddEdge(vector<GL::Point> edge)
{
	edges.push_back(edge);
}

GL::Point GL::Polygon::GetPoint(int index)
{
	return vertices[index];
}

GL::Point GL::Polygon::Check1(int x, int y)
{
	for each (GL::Point p in vertices)
	{
		if ((abs(p.x - x) < 5) && (abs(p.y - y) < 5))
		{
			return p;
		}
	}
	return GL::Point(-1, -1);
}
