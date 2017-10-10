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

GL::Point GL::Polygon::CheckMouseNearVertice(int x, int y)
{
	int maxDistance = 5;
	for each (GL::Point p in vertices)
	{
		if ((abs(p.x - x) < maxDistance) && (abs(p.y - y) < maxDistance))
		{
			return p;
		}
	}
	return GL::Point(-1, -1);
}

vector<GL::Point> GL::Polygon::CheckMouseNearEdge(int x, int y)
{
	int maxDistance = 5;
	for each (vector<GL::Point> edge in edges)
	{
		//bool _val = true;
		for each (GL::Point p in edge)
		{
			if ((abs(p.x - x) < maxDistance) && (abs(p.y - y) < maxDistance))
			{
				return edge;
				//_val = false;
				//break;
			}
		}
		//if (_val == true)
			
	}

	return vector<GL::Point>();
}
