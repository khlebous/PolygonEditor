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

int GL::Polygon::CheckMouseNearVertice(int x, int y)
{
	//TODO regula trojkata
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
	//AddEdge(GetVertice(0), GetVertice(VertCount() - 1));
	//GetEdge(EdgCount() - 1).Draw();
}
