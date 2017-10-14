#include "Polygon.h"
#include <math.h>

GL::Polygon::Polygon()
{
	vertices = vector<GL::Vertice>();
	//edges = vector<GL::Edge>();
}
GL::Polygon::~Polygon()
{
	vertices.clear();
	//for each (Edge v in edges)
	//	v.~Edge();
	//edges.clear();
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
double Distance(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
int GL::Polygon::CheckMouseNearEdge(int x, int y)
{
	if (vertices.size() < 2)
		return -1;
	int i = 0;
	for (; i < vertices.size() - 1; i++)
	{
		if (Distance(vertices[i].GetX(), vertices[i].GetY(), x, y) +
			Distance(vertices[i + 1].GetX(), vertices[i + 1].GetY(), x, y)
			< Distance(vertices[i].GetX(), vertices[i].GetY(),
				vertices[i + 1].GetX(), vertices[i + 1].GetY())
			+ maxDistToHighl)
			return i;
	}
	if (isLooped)
	{
		if (Distance(vertices[i].GetX(), vertices[i].GetY(), x, y) +
			Distance(vertices[0].GetX(), vertices[0].GetY(), x, y)
			< Distance(vertices[i].GetX(), vertices[i].GetY(),
				vertices[0].GetX(), vertices[0].GetY())
			+ maxDistToHighl)
			return i;
	}
	return -1;
}

void GL::Polygon::MoveVertice(int vertNum, int x, int y)
{
	int v1 = (vertNum - 1) % vertices.size();
	int v2 = (vertNum)%vertices.size();
	auto it = std::find(verticalEdges.begin(), verticalEdges.end(), v1);
	if (it != verticalEdges.end())
		vertices[v1].Move(x, vertices[v1].GetY());
	it = std::find(verticalEdges.begin(), verticalEdges.end(), (vertNum) % vertices.size());
	if (it != verticalEdges.end())
		vertices[v2].Move(x, vertices[v2].GetY());
	vertices[vertNum].Move(x, y);
}

void GL::Polygon::DeleteVert(int n)
{
	if (isLooped && vertices.size() < 4)
		return;
	vertices.erase(vertices.begin() + n);
}

void GL::Polygon::MakeEdgeVertical(int n)
{
	auto it = std::find(verticalEdges.begin(), verticalEdges.end(), (n) % vertices.size());
	if (it != verticalEdges.end())
	{
		verticalEdges.remove(n);
	}
	else
	{

		it = std::find(verticalEdges.begin(), verticalEdges.end(), (n - 1) % vertices.size());
		if (it != verticalEdges.end())
			return;
		it = std::find(verticalEdges.begin(), verticalEdges.end(), (n + 1) % vertices.size());
		if (it != verticalEdges.end())
			return;

		int n1 = n;
		int n2 = (n + 1) % vertices.size();

		GL::Vertice v1 = GetVertice(n1);
		GL::Vertice v2 = GetVertice(n2);

		int x = (v1.GetX() + v2.GetX()) / 2;

		vertices[n1] = GL::Vertice(x, v1.GetY());
		vertices[n2] = GL::Vertice(x, v2.GetY());

		verticalEdges.push_back(n);

	}
}

void GL::Polygon::Loop()
{
	if (VertCount() < 3)
		return;
	isLooped = true;
	//AddEdge(GetVertice(0), GetVertice(VertCount() - 1));
	//GetEdge(EdgCount() - 1).Draw();
}
