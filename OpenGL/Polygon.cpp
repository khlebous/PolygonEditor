#include "Polygon.h"
#include <math.h>
#include <iostream>
#define PI 3.14159265
GL::Polygon::Polygon() :isLooped(0)
{
	vertices = vector<GL::Vertex>();
	vEdges = list<int>();
	hEdges = list<int>();

	vertSetAngle = vector<pair<int, float>>();
	edgeCoeff = vector<LineCoefficients>();
}
GL::Polygon::~Polygon()
{
	vertices.clear();
	vEdges.clear();
	hEdges.clear();

	vertSetAngle.clear();
	edgeCoeff.clear();
}

void GL::Polygon::AddVertex(GL::Vertex p)
{
	vertices.push_back(p);
	if (vertices.size() > 1)
		edgeCoeff.push_back(LineCoefficients(vertices[vertices.size() - 1], vertices[vertices.size() - 2]));
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
	if (isLooped == 1)
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
	if (isLooped == 0)
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
	if ((VertCount() < 3) || (isLooped == 1))
		return false;
	isLooped = 1;
	edgeCoeff.push_back(LineCoefficients(vertices[vertices.size() - 1], vertices[0]));
	return true;
}

//vert
void GL::Polygon::MoveVertex(int n, int x, int y)
{
	if (isLooped == 0)
		return;
	bool changes = false;
	GL::Vertex v = vertices[n];
	int xOffset = x - v.GetX();
	int yOffset = y - v.GetY();
	GL::Vertex vOffset = GL::Vertex(xOffset, yOffset);

	int l1 = (n - 1 + vertices.size()) % vertices.size();
	int r1 = (n + 1) % vertices.size();
	int l2 = (n - 2 + vertices.size()) % vertices.size();
	int r2 = (n + 2) % vertices.size();

	if (CheckEdgeVetical(l1))
	{
		changes = true;
		edgeCoeff[l1] = edgeCoeff[l1].FindParallelLine(x, y);
		if (CheckAngleIsSetToVertex(l2))
		{
			GL::Vertex vIntersection = LineIntersection(edgeCoeff[l2], edgeCoeff[l1]);
			vertices[l1].Move(vIntersection.GetX(), vIntersection.GetY());
		}
		else
			vertices[l1].Move(x, vertices[l1].GetY());

		edgeCoeff[n] = edgeCoeff[n].FindParallelLine(x, y);
		if (CheckEdgeHorizontal(n))
		{
			if (CheckAngleIsSetToVertex(r2))
			{
				GL::Vertex vIntersection = LineIntersection(edgeCoeff[n], edgeCoeff[r1]);
				vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());
			}
			else
				vertices[r1].Move(vertices[r1].GetX(), y);
		}
		else if (CheckAngleIsSetToVertex(r1))
		{
			edgeCoeff[n] = edgeCoeff[n].FindParallelLine(x, y);
			GL::Vertex vIntersection = LineIntersection(edgeCoeff[n], edgeCoeff[r1]);
			vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());
		}
	}
	if (CheckEdgeVetical(n))
	{
		changes = true;
		edgeCoeff[n] = edgeCoeff[n].FindParallelLine(x, y);
		if (CheckAngleIsSetToVertex(r2))
		{
			GL::Vertex vIntersection = LineIntersection(edgeCoeff[n], edgeCoeff[r1]);
			vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());
		}
		else
			vertices[r1].Move(x, vertices[r1].GetY());

		edgeCoeff[l1] = edgeCoeff[l1].FindParallelLine(x, y);
		if (CheckEdgeHorizontal(l1))
		{
			if (CheckAngleIsSetToVertex(l2))
			{
				GL::Vertex vIntersection = LineIntersection(edgeCoeff[l1], edgeCoeff[l2]);
				vertices[l1].Move(vIntersection.GetX(), vIntersection.GetY());
			}
			else
				vertices[l1].Move(vertices[l1].GetX(), y);
		}
		else if (CheckAngleIsSetToVertex(l1))
		{
			edgeCoeff[l1] = edgeCoeff[l1].FindParallelLine(x, y);
			GL::Vertex vIntersection = LineIntersection(edgeCoeff[l1], edgeCoeff[l2]);
			vertices[l1].Move(vIntersection.GetX(), vIntersection.GetY());
		}
	}
	if (CheckEdgeHorizontal(l1))
	{
		changes = true;
		edgeCoeff[l1] = edgeCoeff[l1].FindParallelLine(x, y);
		if (CheckAngleIsSetToVertex(l2))
		{
			GL::Vertex vIntersection = LineIntersection(edgeCoeff[l2], edgeCoeff[l1]);
			vertices[l1].Move(vIntersection.GetX(), vIntersection.GetY());
		}
		else
			vertices[l1].Move(vertices[l1].GetX(), y);

		edgeCoeff[n] = edgeCoeff[n].FindParallelLine(x, y);
		if (CheckEdgeVetical(n))
		{
			if (CheckAngleIsSetToVertex(r2))
			{
				GL::Vertex vIntersection = LineIntersection(edgeCoeff[n], edgeCoeff[r1]);
				vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());
			}
			else
				vertices[r1].Move(x, vertices[r1].GetY());
		}
		else if (CheckAngleIsSetToVertex(r1))
		{
			edgeCoeff[n] = edgeCoeff[n].FindParallelLine(x, y);
			GL::Vertex vIntersection = LineIntersection(edgeCoeff[n], edgeCoeff[r1]);
			vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());
		}
	}
	if (CheckEdgeHorizontal(n))
	{
		changes = true;
		edgeCoeff[n] = edgeCoeff[n].FindParallelLine(x, y);
		if (CheckAngleIsSetToVertex(r2))
		{
			GL::Vertex vIntersection = LineIntersection(edgeCoeff[n], edgeCoeff[r1]);
			vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());
		}
		else
			vertices[r1].Move(vertices[r1].GetX(), y);

		edgeCoeff[l1] = edgeCoeff[l1].FindParallelLine(x, y);
		if (CheckEdgeVetical(l1))
		{
			if (CheckAngleIsSetToVertex(l2))
			{
				GL::Vertex vIntersection = LineIntersection(edgeCoeff[l1], edgeCoeff[l2]);
				vertices[l1].Move(vIntersection.GetX(), vIntersection.GetY());
			}
			else
				vertices[l1].Move(x, vertices[l1].GetY());
		}
		else if (CheckAngleIsSetToVertex(l1))
		{
			edgeCoeff[l1] = edgeCoeff[l1].FindParallelLine(x, y);
			GL::Vertex vIntersection = LineIntersection(edgeCoeff[l1], edgeCoeff[l2]);
			vertices[l1].Move(vIntersection.GetX(), vIntersection.GetY());
		}
	}

	if (CheckAngleIsSetToVertex(l1))
	{
		changes = true;
		edgeCoeff[l1] = edgeCoeff[l1].FindParallelLine(x, y);
		GL::Vertex vIntersection = LineIntersection(edgeCoeff[l1], edgeCoeff[l2]);
		vertices[l1].Move(vIntersection.GetX(), vIntersection.GetY());
	}
	if (CheckAngleIsSetToVertex(n))
	{
		changes = true;
		edgeCoeff[l1] = edgeCoeff[l1].FindParallelLine(x, y);
		GL::Vertex vIntersection1 = LineIntersection(edgeCoeff[l1], edgeCoeff[l2]);
		vertices[l1].Move(vIntersection1.GetX(), vIntersection1.GetY());

		edgeCoeff[n] = edgeCoeff[n].FindParallelLine(x, y);
		GL::Vertex vIntersection2 = LineIntersection(edgeCoeff[n], edgeCoeff[r1]);
		vertices[r1].Move(vIntersection2.GetX(), vIntersection2.GetY());
	}
	if (CheckAngleIsSetToVertex(r1))
	{
		changes = true;
		edgeCoeff[n] = edgeCoeff[n].FindParallelLine(x, y);
		GL::Vertex vIntersection = LineIntersection(edgeCoeff[n], edgeCoeff[r1]);
		vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());
	}

	vertices[n].Move(x, y);
	if (!changes)
	{
		UpdateEdgeCoeff(n);
		UpdateEdgeCoeff(l1);
	}

}
void GL::Polygon::AddVertAtEdge(int n, int x, int y)
{
	int n1 = (n + 1) % vertices.size();
	vEdges.remove(n);
	hEdges.remove(n);
	DeleteSetAngle(n);
	DeleteSetAngle(n1);

	vertices.insert(vertices.begin() + n + 1, GL::Vertex(x, y));
	for (auto it = vEdges.begin(); it != vEdges.end(); ++it)
		if ((*it) >= n)
			*it = ((*it + 1) % vertices.size());
	for (auto it = hEdges.begin(); it != hEdges.end(); ++it)
		if ((*it) >= n)
			*it = ((*it + 1) % vertices.size());
	for (auto& el : vertSetAngle)
		if (el.first >= n)
			el.first = (el.first++) % vertices.size();

	edgeCoeff.insert(edgeCoeff.begin() + n, LineCoefficients(vertices[n], vertices[n1]));
	UpdateEdgeCoeff(n1);
}
void GL::Polygon::DeleteVert(int n)
{
	if (!isLooped || (isLooped && vertices.size() < 4))
		return;
	int n1 = (n - 1 + vertices.size()) % vertices.size();
	vEdges.remove(n1);
	vEdges.remove(n);
	hEdges.remove(n1);
	hEdges.remove(n);
	DeleteSetAngle(n1);
	DeleteSetAngle(n);
	DeleteSetAngle((n + 1) % vertices.size());

	vertices.erase(vertices.begin() + n);
	for (auto it = vEdges.begin(); it != vEdges.end(); ++it)
		if ((*it) > n)
			*it = (*it - 1 + vertices.size()) % vertices.size();
	for (auto it = hEdges.begin(); it != hEdges.end(); ++it)
		if ((*it) > n)
			*it = (*it - 1 + vertices.size()) % vertices.size();
	for (auto it = vertSetAngle.begin(); it != vertSetAngle.end(); ++it)
		if ((*it).first > n)
			(*it).first = ((*it).first - 1 + vertices.size()) % vertices.size();

	n1 = (n - 1 + vertices.size()) % vertices.size();
	edgeCoeff.erase(edgeCoeff.begin() + n);
	edgeCoeff[n1] = LineCoefficients(vertices[n1], vertices[n%vertices.size()]);
}

//edge
void GL::Polygon::MakeEdgeVertical(int n)
{
	CheckEdgeVH(n, &vEdges, &hEdges, true);
}
void GL::Polygon::MakeEdgeHorizontal(int n)
{
	CheckEdgeVH(n, &hEdges, &vEdges, false);
}

bool GL::Polygon::EdgeNearVertical(int n)
{
	int n1 = (n + 1) % vertices.size();
	if (fabs(vertices[n].GetX() - vertices[n1].GetX()) < 10)
		return true;
	else
		return false;
}

bool GL::Polygon::EdgeNearHorizontal(int n)
{

	int n1 = (n + 1) % vertices.size();
	if (fabs(vertices[n].GetY() - vertices[n1].GetY()) < 5)
		return true;
	else
		return false;
}

//angle
bool GL::Polygon::SetAngleFunction(int n)
{
	if (isLooped == 0)
		return false;
	if (CheckAngleIsSetToVertex(n))
	{
		DeleteSetAngle(n);
		return false;
	}

	int l1 = (n - 1 + vertices.size()) % vertices.size();
	int r1 = (n + 1) % vertices.size();
	if ((isLooped == 1) || (n != 0 && (n + 1) != vertices.size()))
	{
		if (CheckAngleIsSetToVertex(l1) || CheckAngleIsSetToVertex(r1))
			return false;
		if (CheckEdgeVetical(l1) || CheckEdgeHorizontal(l1)
			|| CheckEdgeVetical(n) || CheckEdgeHorizontal(n))
			return false;
		GL::Vertex v = GetVertex(n);
		GL::Vertex v_l1 = GetVertex(l1);
		GL::Vertex v_r1 = GetVertex(r1);

		int x1 = v_l1.GetX() - v.GetX();	int x2 = v_r1.GetX() - v.GetX();
		int y1 = v_l1.GetY() - v.GetY();	int y2 = v_r1.GetY() - v.GetY();
		float dot = x1*x2 + y1*y2;
		float angleRad = acos((dot / (sqrt(x1*x1 + y1*y1)*sqrt(x2*x2 + y2*y2))));
		float angle = acos((dot / (sqrt(x1*x1 + y1*y1)*sqrt(x2*x2 + y2*y2))))* 180.0 / PI;

		std::cin.clear();
		cout << "angle : " << angle << "\n";
		float newAngle = -1;
		cout << "wnter your angle: ";
		cin >> newAngle;
		if (newAngle == -1)
			newAngle = angle;
		cout << "new angle : " << newAngle << "\n";
		newAngle = newAngle / 180.0*PI;
		GL::Vertex v_sr = GL::Vertex((v_l1.GetX() + v_r1.GetX()) / 2, (v_l1.GetY() + v_r1.GetY()) / 2);

		int x = v_l1.GetX() - v_sr.GetX();
		int y = v_l1.GetY() - v_sr.GetY();
		int x_rot = -y;
		int y_rot = x;
		if ((v_l1.GetX() - v_sr.GetX())*(v.GetY() - v_sr.GetY()) - (v_l1.GetY() - v_sr.GetY())*(v.GetX() - v_sr.GetX()) < 0)
		{
			x_rot = y;
			y_rot = -x;
		}
		
		double a = Distance(v_l1.GetX(), v_l1.GetY(), v_sr.GetX(), v_sr.GetY());
		int b = a / tan(newAngle/2);

		x_rot = x_rot / a*b + v_sr.GetX();
		y_rot = y_rot / a*b+ v_sr.GetY();

		MoveVertex(n, x_rot, y_rot);

		vertSetAngle.push_back(make_pair(n, angle));
		return true;
	}
	return false;
}

//polygon
void GL::Polygon::MovePolygon(int xOffset, int yOffset)
{
	GL::Vertex vOffset = GL::Vertex(xOffset, yOffset);
	for (GL::Vertex &v : vertices)
		v = v + vOffset;
	UpdateAllEdgeCoeff();
}

//================================================================
//private
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
		return;;
	{
		if ((isLooped == 1) || (n != 0))
		{
			it = std::find((*v1).begin(), (*v1).end(), (n - 1 + vertices.size()) % vertices.size());
			if (it != (*v1).end())
				return;
		}
		if ((isLooped == 1) || (n + 1 != vertices.size() - 1))
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
			if (abs(v1.GetX() - v2.GetX()) > abs(v1.GetY() - v2.GetY()))
				return;
			int x = (v1.GetX() + v2.GetX()) / 2;
			vertices[n1] = GL::Vertex(x, v1.GetY());
			vertices[n2] = GL::Vertex(x, v2.GetY());
			vEdges.push_back(n);
		}
		else
		{
			if (abs(v1.GetX() - v2.GetX()) < abs(v1.GetY() - v2.GetY()))
				return;
			int y = (v1.GetY() + v2.GetY()) / 2;
			vertices[n1] = GL::Vertex(v1.GetX(), y);
			vertices[n2] = GL::Vertex(v2.GetX(), y);
			hEdges.push_back(n);
		}
	}
	UpdateEdgeCoeff(n);
	int l1 = (n - 1 + vertices.size()) % vertices.size();
	int r1 = (n + 1) % vertices.size();
	int r2 = (n + 2) % vertices.size();
	if (CheckAngleIsSetToVertex(l1))
	{
		GL::Vertex v = LineIntersection(edgeCoeff[l1], edgeCoeff[n]);
		vertices[n].Move(v.GetX(), v.GetY());
	}
	if (CheckAngleIsSetToVertex(r2))
	{
		GL::Vertex v = LineIntersection(edgeCoeff[r1], edgeCoeff[n]);
		vertices[r1].Move(v.GetX(), v.GetY());
	}
}

bool GL::Polygon::CheckAngleIsSetToVertex(int n)
{
	for (auto& a : vertSetAngle)
		if (a.first == n)
			return true;
	return false;
}
void GL::Polygon::UpdateAllEdgeCoeff()
{
	edgeCoeff.clear();
	for (int i = 0; i < vertices.size() - 1; i++)
	{
		edgeCoeff.push_back(LineCoefficients(vertices[i], vertices[i + 1]));
	}
	edgeCoeff.push_back(LineCoefficients(vertices[0], vertices[vertices.size() - 1]));
}
void GL::Polygon::UpdateEdgeCoeff(int n)
{
	if ((n >= vertices.size()) || n < 0)
	{
		cout << "incorrect n in UpdateEdgeCoeff\n";
		return;
	}
	edgeCoeff[n] = LineCoefficients(LineCoefficients(vertices[n], vertices[(n + 1) % vertices.size()]));
}
void GL::Polygon::DeleteSetAngle(int n)
{
	auto it = vertSetAngle.begin();
	while (it != vertSetAngle.end())
	{
		if ((*it).first == n)
		{
			vertSetAngle.erase(it++);
			return;
		}
		else
			++it;
	}
}

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
