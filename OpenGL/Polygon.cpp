#include "Polygon.h"
#include <math.h>
#include <iostream>
#define PI 3.14159265
GL::Polygon::Polygon()
{
	vertices = vector<GL::Vertex>();
	vEdges = list<int>();
	hEdges = list<int>();
	angles = vector<pair<int, float>>();
	//edges = vector<GL::Edge>();
}
GL::Polygon::~Polygon()
{
	vertices.clear();
	vEdges.clear();
	hEdges.clear();
	angles.clear();
	//for each (Edge v in edges)
	//	v.~Edge();
	//edges.clear();
}

int GL::Polygon::CheckMouseNearVertice(int x, int y)
{
	int i = 0;
	for (GL::Vertex& v : vertices)
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

void GL::Polygon::MoveVertex(int vertNum, int x, int y)
{
	int e1 = (vertNum - 1 + vertices.size()) % vertices.size();
	int e2 = (vertNum + 1) % vertices.size();

	if (isLooped || (vertNum != 0))
	{
		if (CheckEdgeVetical(e1))
			vertices[e1].Move(x, vertices[e1].GetY());
		if (CheckEdgeHorizontal(e1))
			vertices[e1].Move(vertices[e1].GetX(), y);
	}
	if (isLooped || (vertNum + 1 != vertices.size()))
	{
		if (CheckEdgeVetical(vertNum))
			vertices[e2].Move(x, vertices[e2].GetY());
		if (CheckEdgeHorizontal(vertNum))
			vertices[e2].Move(vertices[e2].GetX(), y);
	}

	vertices[vertNum].Move(x, y);
}
void GL::Polygon::AddVert(int n, int x, int y)
{
	vEdges.remove(n);
	hEdges.remove(n);
	DeleteVertFromAngleVector(n);
	DeleteVertFromAngleVector(n+1);

	vertices.insert(vertices.begin() + n + 1, GL::Vertex(x, y));
	for (auto it = vEdges.begin(); it != vEdges.end(); ++it)
		if ((*it) >= n)
			(*it)++;
	for (auto it = hEdges.begin(); it != hEdges.end(); ++it)
		if ((*it) >= n)
			(*it)++;
	for (auto it = angles.begin(); it != angles.end(); ++it)
		if ((*it).first > n)
			(*it).first++;
}
void GL::Polygon::DeleteVert(int n)
{
	if (isLooped && vertices.size() < 4)
		return;
	int n1 = (n - 1 + vertices.size()) % vertices.size();
	vEdges.remove(n1);
	vEdges.remove(n);
	hEdges.remove(n1);
	hEdges.remove(n);
	DeleteVertFromAngleVector(n1);
	DeleteVertFromAngleVector(n);
	DeleteVertFromAngleVector((n+1)%vertices.size());

	vertices.erase(vertices.begin() + n);
	for (auto it = vEdges.begin(); it != vEdges.end(); ++it)
		if ((*it) > n)
			(*it)--;
	for (auto it = hEdges.begin(); it != hEdges.end(); ++it)
		if ((*it) > n)
			(*it)--;

	for (auto it = angles.begin(); it != angles.end(); ++it)
		if ((*it).first > n)
			(*it).first--;
}
//TODO return true/false
void GL::Polygon::MakeEdgeVertical(int n)
{
	CheckEdgeVH(n, &vEdges, &hEdges, true);
}
void GL::Polygon::MakeEdgeHorizontal(int n)
{
	CheckEdgeVH(n, &hEdges, &vEdges, false);
}
bool GL::Polygon::SetAngle(int n)
{
	if (!isLooped)
		return false;
	if (CheckVertAngle(n))
	{
		DeleteVertFromAngleVector(n);
		return false;
	}
	int n1 = (n - 1 + vertices.size()) % vertices.size();
	if (CheckVertAngle(n1) || CheckVertAngle((n + 1) % vertices.size()))
		return false;
	if (CheckEdgeVetical(n1) || CheckEdgeHorizontal(n1)
		|| CheckEdgeVetical(n) || CheckEdgeHorizontal(n))
		return false;

	GL::Vertex v = GetVertex(n);
	GL::Vertex v1 = GetVertex(n1);
	GL::Vertex v2 = GetVertex((n + 1) % vertices.size());

	int x1 = v1.GetX() - v.GetX();	int x2 = v2.GetX() - v.GetX();
	int y1 = v1.GetY() - v.GetY();	int y2 = v2.GetY() - v.GetY();
	float dot = x1*x2 + y1*y2;
	float angle = acos((dot / (sqrt(x1*x1 + y1*y1)*sqrt(x2*x2 + y2*y2))))* 180.0 / PI;

	std::cin.clear();
	cout << "angle : " << angle << "\n";
	//cout << "Enter angle\n";
	//float a;
	//cin >> a;
	//cout << "Your angle: " << a << " degrees\n\n";

	angles.push_back(make_pair(n, angle));

	return true;
}

void GL::Polygon::Loop()
{
	if (VertCount() < 3)
		return;
	isLooped = true;
	//AddEdge(GetVertex(0), GetVertex(VertCount() - 1));
	//GetEdge(EdgCount() - 1).Draw();
}

bool GL::Polygon::CheckEdgeVetical(int n)
{
	auto it = std::find(vEdges.begin(), vEdges.end(), n);
	if (it != vEdges.end())
		return true;
	else
		return false;
}
bool GL::Polygon::CheckEdgeHorizontal(int n)
{
	auto it = std::find(hEdges.begin(), hEdges.end(), n);
	if (it != hEdges.end())
		return true;
	else
		return false;
}
void GL::Polygon::CheckEdgeVH(int n, list<int>* v1, list<int>* v2, bool checkV)
{
	auto it = std::find((*v2).begin(), (*v2).end(), n);
	if (it != (*v2).end())
		return;
	it = std::find((*v1).begin(), (*v1).end(), n);
	if (it != (*v1).end())
	{
		(*v1).remove(n);
		return;
	}
	if (CheckVertAngle(n) || CheckVertAngle((n + 1) % vertices.size()))
		return;
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
		GL::Vertex v1 = GetVertex(n1);
		GL::Vertex v2 = GetVertex(n2);
		if (checkV)
		{
			int x = (v1.GetX() + v2.GetX()) / 2;
			vertices[n1] = GL::Vertex(x, v1.GetY());
			vertices[n2] = GL::Vertex(x, v2.GetY());
			vEdges.push_back(n);
		}
		else
		{
			int y = (v1.GetY() + v2.GetY()) / 2;
			vertices[n1] = GL::Vertex(v1.GetX(), y);
			vertices[n2] = GL::Vertex(v2.GetX(), y);
			hEdges.push_back(n);
		}
	}
}

void GL::Polygon::DeleteVertFromAngleVector(int n)
{
	auto itr = angles.begin();
	while (itr != angles.end())
	{
		if ((*itr).first == n)
		{
			angles.erase(itr++);
			return;
		}
		else
			++itr;
	}
}

bool GL::Polygon::CheckVertAngle(int n)
{
	for (auto& a : angles)
		if (a.first == n)
			return true;
	return false;
}
