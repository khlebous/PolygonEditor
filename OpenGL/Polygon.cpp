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
	linesNearVertWithSetAngle = vector<pair<int, pair<LineCoefficients, LineCoefficients>>>();
	linesNearVertWithSetAngle1 = vector<pair<int, pair<LineCoefficients, LineCoefficients>>>();
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

	// TODO del
	GL::Vertex v = vertices[vertNum];
	int xOffset = x - v.GetX();
	int yOffset = y - v.GetY();
	GL::Vertex vOffset = GL::Vertex(xOffset, yOffset);

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


	if (isLooped || ((vertNum != 0) && (vertNum + 1 != vertices.size())))
	{
		if (CheckAngleIsSetToVertex(vertNum - 1))
		{

		}
		if (CheckAngleIsSetToVertex(vertNum))
		{
			pair<LineCoefficients, LineCoefficients>* lc1 = nullptr;
			for (auto& el : linesNearVertWithSetAngle1)
				if (el.first == vertNum)
				{
					lc1 = &(el.second);
					break;
				}
			if (lc1 == nullptr)
				throw std::exception();
			(*lc1).first.ChangeCoefficientsToParallelLine(x, y);
			(*lc1).second.ChangeCoefficientsToParallelLine(x, y);
			pair<LineCoefficients, LineCoefficients>* lc = nullptr;
			for (auto& el : linesNearVertWithSetAngle)
				if (el.first == vertNum)
				{
					lc = &(el.second);
					break;
				}
			if (lc == nullptr)
				throw std::exception();
			else
			{

				//cout << "oX= " << xOffset << " oY= " << yOffset << "\n";
				GL::Vertex v0 = vOffset + v;
				GL::Vertex v1 = vertices[e1];
				GL::Vertex v2 = vertices[e2];
				GL::Vertex v3 = v2 + vOffset;
				GL::Vertex v4 = v1 + vOffset;
				int param = 5;

				/*GL::Vertex vIntersection = LineIntersection(v0, v3, lc->second);
				vertices[e2].Move(vIntersection.GetX(), vIntersection.GetY());
				GL::Vertex vIntersection2 = LineIntersection(v0, v4, lc->first);
				vertices[e1].Move(vIntersection2.GetX(), vIntersection2.GetY());*/
				
				GL::Vertex vIntersection = LineIntersection(lc1->second, lc->second);
				vertices[e2].Move(vIntersection.GetX(), vIntersection.GetY());
				GL::Vertex vIntersection2 = LineIntersection(lc1->first, lc->first);
				vertices[e1].Move(vIntersection2.GetX(), vIntersection2.GetY());
			}
		}
		if (CheckAngleIsSetToVertex(vertNum + 1))
		{

		}
	}

	vertices[vertNum].Move(x, y);
}
void GL::Polygon::AddVert(int n, int x, int y)
{
	vEdges.remove(n);
	hEdges.remove(n);
	DeleteVertFromAngleVector(n);
	DeleteVertFromAngleVector(n + 1);

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
	DeleteVertFromAngleVector((n + 1) % vertices.size());

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
	if (CheckAngleIsSetToVertex(n))
	{
		DeleteVertFromAngleVector(n);
		return false;
	}

	int n1 = (n - 1 + vertices.size()) % vertices.size();
	if (isLooped || (n != 0 && (n + 1) != vertices.size()))
	{
		if (CheckAngleIsSetToVertex(n1) || CheckAngleIsSetToVertex((n + 1) % vertices.size()))
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
		LineCoefficients lc1 = LineCoefficients(v1, GetVertex((n - 2 + vertices.size()) % vertices.size()));
		LineCoefficients lc2 = LineCoefficients(v2, GetVertex((n + 2) % vertices.size()));
		linesNearVertWithSetAngle.push_back(make_pair(n, make_pair(lc1, lc2)));

		LineCoefficients lc3 = LineCoefficients(v, v1);
		LineCoefficients lc4 = LineCoefficients(v, v2);
		linesNearVertWithSetAngle1.push_back(make_pair(n, make_pair(lc3, lc4)));

		return true;
	}
	return false;

}

void GL::Polygon::Loop()
{
	if (VertCount() < 3)
		return;
	isLooped = true;
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
	if (CheckAngleIsSetToVertex(n) || CheckAngleIsSetToVertex((n + 1) % vertices.size()))
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

GL::Vertex GL::Polygon::LineIntersection(GL::Vertex v1, GL::Vertex v2, GL::Vertex v3, GL::Vertex v4)
{
	cout << "v1 = " << v1;
	cout << "v2 = " << v2;
	cout << "v3 = " << v3;
	cout << "v4 = " << v4;
	int A1 = v2.GetY() - v1.GetY();
	int B1 = v1.GetX() - v2.GetX();
	int C1 = A1*v1.GetX() + B1*v1.GetY();

	int A2 = v4.GetY() - v3.GetY();
	int B2 = v3.GetX() - v4.GetX();
	int C2 = A2*v3.GetX() + B2*v3.GetY();

	double det = A1*B2 - A2*B1;
	if (det == 0)
	{
		//blad
	}
	else
	{
		double x = (B2*C1 - B1*C2) / det;
		//double y = (A1*C2 - A2*C1) / det;
		double y = x*v4.GetY() / v4.GetX();
		cout << "x= " << x << " y= " << y << "\n";
		int y1 = round(y);
		return GL::Point(round(x), round(y));
	}
	return GL::Point(-1, -1);
}

GL::Vertex GL::Polygon::LineIntersection(GL::LineCoefficients lc1, GL::LineCoefficients lc2)
{
	int A1 = lc1.GetA();
	int B1 = lc1.GetB();
	int C1 = lc1.GetC();

	int A2 = lc2.GetA();
	int B2 = lc2.GetB();
	int C2 = lc2.GetC();
	cout << "A2 = " << A2;
	cout << " B2 = " << B2;
	cout << " C1 = " << C1 << "\n";

	double det = A1*B2 - A2*B1;
	cout << " det = " << det << "\n";

	if (det == 0)
	{
		//return v1;
	}
	else
	{
		double x = (B2*C1 - B1*C2) / det;
		double y = (A1*C2 - A2*C1) / det;
		//double y = x*v4.GetY() / v4.GetX();
		cout << "x= " << x << " y= " << y << "\n";
		int y1 = round(y);
		return GL::Point(round(x), round(y));
	}
	return GL::Point(-1, -1);
}

GL::Vertex GL::Polygon::LineIntersection(GL::Vertex v1, GL::Vertex v2, GL::LineCoefficients lc2)
{
	//cout << " v1 = " << v1;
	//cout << " v2 = " << v2;
	//cout << "v3 = " << v3;
	//cout << "v4 = " << v4;
	int A1 = v2.GetY() - v1.GetY();
	int B1 = v1.GetX() - v2.GetX();
	int C1 = A1*v1.GetX() + B1*v1.GetY();

	int A2 = lc2.GetA();
	int B2 = lc2.GetB();
	int C2 = lc2.GetC();
	cout << "A2 = " << A2;
	cout << " B2 = " << B2;
	cout << " C1 = " << C1 << "\n";

	double det = A1*B2 - A2*B1;
	cout << " det = " << det << "\n";

	if (det == 0)
	{
		//return v1;
	}
	else
	{
		double x = (B2*C1 - B1*C2) / det;
		double y = (A1*C2 - A2*C1) / det;
		//double y = x*v4.GetY() / v4.GetX();
		cout << "x= " << x << " y= " << y << "\n";
		int y1 = round(y);
		return GL::Point(round(x), round(y));
	}
	return GL::Point(-1, -1);
}

bool GL::Polygon::CheckAngleIsSetToVertex(int n)
{
	for (auto& a : angles)
		if (a.first == n)
			return true;
	return false;
}
