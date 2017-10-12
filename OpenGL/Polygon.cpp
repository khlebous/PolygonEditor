#define _CRT_SECURE_NO_WARNINGS
#include "Polygon.h"

GL::Polygon::Polygon()
{
	vertices = vector<GL::Vertice>();
	edges = vector<GL::Edge>();
}
GL::Polygon::~Polygon()
{
	vertices.clear();
	for each (Edge v in edges)
		v.~Edge();
	edges.clear();
}

void GL::Polygon::AddVertice(int x, int y)
{
	vertices.push_back(GL::Vertice(x, y));
}
void GL::Polygon::AddVertice(GL::Point p)
{
	vertices.push_back(GL::Vertice(p));
}
void GL::Polygon::AddEdge(GL::Vertice v1, GL::Vertice v2)
{
	edges.push_back(GL::Edge(v1, v2));
}

GL::Vertice GL::Polygon::GetVertice(int index)
{
	return vertices[index];
}
GL::Edge GL::Polygon::GetEdge(int index)
{
	return edges[index];
}

int GL::Polygon::CheckMouseNearVertice(int x, int y)
{
	int i = 0;
	for (GL::Vertice& v : vertices)
	{
		if ((abs(v.GetX() - x) < maxDistToHighl) && (abs(v.GetY() - y) < maxDistToHighl))
			return i;
		i++;
	}
	return -1;
}
int GL::Polygon::CheckMouseNearEdge(int x, int y)
{
	int i = 0;
	for (GL::Edge& edge : edges)
	{
		if (edge.IsPointNear(x, y, maxDistToHighl))
			return i;
		i++;
	}
	return -1;
}

void GL::Polygon::Loop()
{
	if (VertCount() < 3)
		return;
	isLooped = true;
	AddEdge(GetVertice(0), GetVertice(VertCount() - 1));
	GetEdge(EdgCount() - 1).Draw();
}
