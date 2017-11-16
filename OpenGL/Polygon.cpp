#include "Polygon.h"
#include <math.h>
#include <iostream>
#define PI 3.14159265
GL::Polygon::Polygon() :isLooped(0)
{
	vertices = vector<GL::Vertex>();
	isLooped = false;
}
GL::Polygon::~Polygon()
{
	vertices.clear();
}
void GL::Polygon::AddVertex(GL::Vertex p)
{
	vertices.push_back(p);
}
int GL::Polygon::CheckMouseNearVertice(int x, int y)
{
	int i = 0;
	for (GL::Vertex& v : vertices)
	{
		if ((abs(v.GetX() - x) < 5) && (abs(v.GetY() - y) < 5))
			return i;
		i++;
	}
	return -1;
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
			+ 5)
			return i;
	}
	if (isLooped)
	{
		if (Distance(vertices[i].GetX(), vertices[i].GetY(), x, y) +
			Distance(vertices[0].GetX(), vertices[0].GetY(), x, y)
			< Distance(vertices[i].GetX(), vertices[i].GetY(),
				vertices[0].GetX(), vertices[0].GetY())
			+ 5)
			return i;
	}
	return -1;
}
bool GL::Polygon::IsInside(int x, int y)
{
	if (!isLooped)
		return false;
	int i, j, nvert = vertices.size();
	bool c = false;

	for (i = 0, j = nvert - 1; i < nvert; j = i++)
	{
		if ((vertices[i].GetY() > y) != (vertices[j].GetY() > y) &&
			x <= (vertices[j].GetX() - vertices[i].GetX()) * (y - vertices[i].GetY()) / (vertices[j].GetY() - vertices[i].GetY()) + vertices[i].GetX())
			c = !c;
	}
	return c;
}
bool GL::Polygon::Loop()
{
	if ((VertCount() < 3) || (isLooped))
		return false;
	isLooped=true;
	return true;
}

//vert
void GL::Polygon::MoveVertex(int n, int x, int y)
{
	vertices[n].Move(x, y);
}
void GL::Polygon::AddVertAtEdge(int n, int x, int y)
{
	int n1 = (n + 1) % vertices.size();
	vertices.insert(vertices.begin() + n + 1, GL::Vertex(x, y));
}
void GL::Polygon::DeleteVert(int n)
{
	if (isLooped && vertices.size() < 4)
		return;
	int n1 = (n - 1 + vertices.size()) % vertices.size();
	vertices.erase(vertices.begin() + n);
}

//polygon
void GL::Polygon::MovePolygon(int xOffset, int yOffset)
{
	GL::Vertex vOffset = GL::Vertex(xOffset, yOffset);
	for (GL::Vertex &v : vertices)
		v = v + vOffset;
}
bool GL::Polygon::CheckConvex()
{
	if (!isLooped)
		return false;
	int n = vertices.size();
	int i, j, k;
	int flag = 0;
	double z;

	for (i = 0; i < n; i++) {
		j = (i + 1) % n;
		k = (i + 2) % n;
		z = (vertices[j].GetX() - vertices[i].GetX()) * (vertices[k].GetY() - vertices[j].GetY());
		z -= (vertices[j].GetY() - vertices[i].GetY()) * (vertices[k].GetX() - vertices[j].GetX());
		if (z < 0)
			flag |= 1;
		else if (z > 0)
			flag |= 2;
		if (flag == 3)
			return false;
	}
	if (flag != 0)
		return true;
	else
		return false;
}

//================================================================
//private

double GL::Polygon::Distance(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
GL::Vertex GL::Polygon::LineIntersection(GL::LineCoefficients lc1, GL::LineCoefficients lc2)
{
	int A1 = lc1.GetA();
	int B1 = lc1.GetB();
	int C1 = lc1.GetC();

	int A2 = lc2.GetA();
	int B2 = lc2.GetB();
	int C2 = lc2.GetC();

	double det = A1*B2 - A2*B1;

	if (det == 0)
	{
	}
	else
	{
		double x = (B2*C1 - B1*C2) / det;
		double y = (A1*C2 - A2*C1) / det;
		return GL::Vertex(round(x), round(y));
	}
	return GL::Vertex(-1, -1);
}
