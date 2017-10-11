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

GL::Vertice GL::Polygon::CheckMouseNearVertice(int x, int y)
{
	for(GL::Vertice& v : vertices)
		if ((abs(v.GetX() - x) < maxDistance) && (abs(v.GetY() - y) < maxDistance))
			return v;
	return GL::Vertice(-1, -1);
}
GL::Edge GL::Polygon::CheckMouseNearEdge(int x, int y)
{
	for (GL::Edge& edge : edges)
		if (edge.IsPointNear(x, y, maxDistance))
			return edge;
	return GL::Edge();
}
