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
	/*int a1 = vertNum - 1;
	int a2 = vertices.size();
	int a3 = a1 % a2;
	int a4 = -1 % 10;
	int a5 = -3 % 10;*/
	int e1 = (vertNum - 1 + vertices.size()) % vertices.size();
	int e2 = (vertNum + 1) % vertices.size();

	if (isLooped || (vertNum != 0))
	{
		auto it = std::find(vEdges.begin(), vEdges.end(), e1);
		if (it != vEdges.end())
			vertices[e1].Move(x, vertices[e1].GetY());
		it = std::find(hEdges.begin(), hEdges.end(), e1);
		if (it != hEdges.end())
			vertices[e1].Move(vertices[e1].GetX(), y);
	}

	if (isLooped || (vertNum + 1 != vertices.size()))
	{
		auto it = std::find(vEdges.begin(), vEdges.end(), vertNum);
		if (it != vEdges.end())
			vertices[e2].Move(x, vertices[e2].GetY());
		it = std::find(hEdges.begin(), hEdges.end(), vertNum);
		if (it != hEdges.end())
			vertices[e2].Move(vertices[e2].GetX(), y);
	}

	vertices[vertNum].Move(x, y);
}
void GL::Polygon::AddVert(int n, int x, int y)
{
	vEdges.remove(n);
	hEdges.remove(n);
	vertices.insert(vertices.begin() + n + 1, GL::Vertice(x, y));
	for (auto it = vEdges.begin(); it != vEdges.end(); ++it)
	{
		if ((*it) >= n)
			(*it)++;
	}
	for (auto it = hEdges.begin(); it != hEdges.end(); ++it)
		if ((*it) >= n)
			(*it)++;
	//vertices.push_back(GL::Vertice(x, y));
}
void GL::Polygon::DeleteVert(int n)
{
	if (isLooped && vertices.size() < 4)
		return;
	vEdges.remove(n - 1);
	vEdges.remove(n);
	hEdges.remove(n - 1);
	hEdges.remove(n);
	vertices.erase(vertices.begin() + n);
	for (auto it = vEdges.begin(); it != vEdges.end(); ++it)
	{
		if ((*it) > n)
			(*it)--;
	}
	for (auto it = hEdges.begin(); it != hEdges.end(); ++it)
		if ((*it) > n)
			(*it)--;
}

void GL::Polygon::MakeEdgeVertical(int n)
{
	CheckEdgeVH(n, &vEdges, &hEdges, true);
}
void GL::Polygon::MakeEdgeHorizontal(int n)
{
	CheckEdgeVH(n, &hEdges, &vEdges, false);
}

void GL::Polygon::Loop()
{
	if (VertCount() < 3)
		return;
	isLooped = true;
	//AddEdge(GetVertice(0), GetVertice(VertCount() - 1));
	//GetEdge(EdgCount() - 1).Draw();
}

void GL::Polygon::CheckEdgeVH(int n, list<int>* v1, list<int>* v2, bool checkV)
{
	auto it = std::find((*v2).begin(), (*v2).end(), n);
	if (it != (*v2).end())
		return;
	it = std::find((*v1).begin(), (*v1).end(), n);
	if (it != (*v1).end())
 		(*v1).remove(n);
	else
	{
		if (isLooped || (n != 0))
		{
			it = std::find((*v1).begin(), (*v1).end(), (n - 1 + vertices.size()) % vertices.size());
			if (it != (*v1).end())
				return;
		}
		if (isLooped || (n + 1 != vertices.size() - 1))
		{
			it = std::find((*v1).begin(), (*v1).end(), (n + 1) % vertices.size());
			if (it != (*v1).end())
				return;
		}

		int n1 = n;
		int n2 = (n + 1) % vertices.size();
		GL::Vertice v1 = GetVertice(n1);
		GL::Vertice v2 = GetVertice(n2);
		if (checkV)
		{
			int x = (v1.GetX() + v2.GetX()) / 2;
			vertices[n1] = GL::Vertice(x, v1.GetY());
			vertices[n2] = GL::Vertice(x, v2.GetY());
			vEdges.push_back(n);
		}
		else
		{
			int y = (v1.GetY() + v2.GetY()) / 2;
			vertices[n1] = GL::Vertice(v1.GetX(), y);
			vertices[n2] = GL::Vertice(v2.GetX(), y);
			hEdges.push_back(n);
		}
	}
}
