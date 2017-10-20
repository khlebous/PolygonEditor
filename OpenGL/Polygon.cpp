#include "Polygon.h"
#include <math.h>
#include <iostream>
#define PI 3.14159265
GL::Polygon::Polygon()
{
	vertices = vector<GL::Vertex>();
	vEdges = list<int>();
	hEdges = list<int>();
	angles = vector<int>();
	//edges = vector<GL::Edge>();
	//linesNearVertWithSetAngle = vector<pair<int, pair<LineCoefficients, LineCoefficients>>>();
	//linesNearNearVertWithSetAngle = vector<pair<int, pair<LineCoefficients, LineCoefficients>>>();
	setAngle = vector<SetAngle>();
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

	int l1 = (vertNum - 1 + vertices.size()) % vertices.size();
	int r1 = (vertNum + 1) % vertices.size();
	int l2 = (vertNum - 2 + vertices.size()) % vertices.size();
	int r2 = (vertNum + 2) % vertices.size();

	if (isLooped || (vertNum != 0))
	{
		if (CheckEdgeVetical(l1))
		{
			if (CheckAngleIsSetToVertex(l2))
			{
				SetAngle* sa = nullptr;
				for (auto& el : setAngle)
				{
					if (el.GetVertexNumber() == l2)
					{
						sa = &el;
						break;
					}
				}
				sa->SetLC_R2(sa->GetLC_R2().FindParallelLine(x, y));
				GL::Vertex vIntersection = LineIntersection(sa->GetLC_R1(), sa->GetLC_R2());
				vertices[l1].Move(vIntersection.GetX(), vIntersection.GetY());
			}
			else
				vertices[l1].Move(x, vertices[l1].GetY());
		}
		if (CheckEdgeHorizontal(l1))
		{
			if (CheckAngleIsSetToVertex(l2))
			{
				SetAngle* sa = nullptr;
				for (auto& el : setAngle)
				{
					if (el.GetVertexNumber() == l2)
					{
						sa = &el;
						break;
					}
				}
				sa->SetLC_R2(sa->GetLC_R2().FindParallelLine(x, y));
				GL::Vertex vIntersection = LineIntersection(sa->GetLC_R1(), sa->GetLC_R2());
				vertices[l1].Move(vIntersection.GetX(), vIntersection.GetY());
			}
			else
				vertices[l1].Move(vertices[l1].GetX(), y);

		}

	}
	if (isLooped || (vertNum + 1 != vertices.size()))
	{
		if (CheckEdgeVetical(vertNum))
		{
			if (CheckAngleIsSetToVertex(r2))
			{
				SetAngle* sa = nullptr;
				for (auto& el : setAngle)
				{
					if (el.GetVertexNumber() == r2)
					{
						sa = &el;
						break;
					}
				}
				sa->SetLC_L2(sa->GetLC_L2().FindParallelLine(x, y));
				GL::Vertex vIntersection = LineIntersection(sa->GetLC_L1(), sa->GetLC_L2());
				vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());
			}
			else
				vertices[r1].Move(x, vertices[r1].GetY());
		}
		if (CheckEdgeHorizontal(vertNum))
		{
			if (CheckAngleIsSetToVertex(r2))
			{
				SetAngle* sa = nullptr;
				for (auto& el : setAngle)
				{
					if (el.GetVertexNumber() == r2)
					{
						sa = &el;
						break;
					}
				}
				sa->SetLC_L2(sa->GetLC_L2().FindParallelLine(x, y));
				GL::Vertex vIntersection = LineIntersection(sa->GetLC_L1(), sa->GetLC_L2());
				vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());
			}
			else
				vertices[r1].Move(vertices[r1].GetX(), y);
		}
	}

	if (isLooped || ((vertNum != 0) && (vertNum + 1 != vertices.size())))
	{
		if (CheckAngleIsSetToVertex(l1))
		{
			SetAngle* sa = nullptr;
			for (auto& el : setAngle)
			{
				if (el.GetVertexNumber() == l1)
				{
					sa = &el;
					break;
				}
			}
			sa->SetLC_R1(sa->GetLC_R1().FindParallelLine(x, y));
			GL::Vertex vIntersection = LineIntersection(sa->GetLC_L1(), sa->GetLC_R1());
			vertices[l1].Move(vIntersection.GetX(), vIntersection.GetY());
		}
		if (CheckAngleIsSetToVertex(vertNum))
		{
			SetAngle* sa = nullptr;
			for (auto& el : setAngle)
			{
				if (el.GetVertexNumber() == vertNum)
				{
					sa = &el;
					break;
				}
			}
			sa->SetLC_R1(sa->GetLC_R1().FindParallelLine(x, y));
			GL::Vertex vIntersection = LineIntersection(sa->GetLC_R1(), sa->GetLC_R2());
			vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());

			sa->SetLC_L1(sa->GetLC_L1().FindParallelLine(x, y));
			GL::Vertex vIntersection2 = LineIntersection(sa->GetLC_L1(), sa->GetLC_L2());
			vertices[l1].Move(vIntersection2.GetX(), vIntersection2.GetY());
			/*
			pair<LineCoefficients, LineCoefficients>* lc1 = nullptr;
			for (auto& el : linesNearNearVertWithSetAngle)
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

			GL::Vertex vIntersection = LineIntersection(lc1->second, lc->second);
			vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());
			GL::Vertex vIntersection2 = LineIntersection(lc1->first, lc->first);
			vertices[l1].Move(vIntersection2.GetX(), vIntersection2.GetY());*/
		}
		if (CheckAngleIsSetToVertex(r1))
		{
			SetAngle* sa = nullptr;
			for (auto& el : setAngle)
			{
				if (el.GetVertexNumber() == r1)
				{
					sa = &el;
					break;
				}
			}
			sa->SetLC_L1(sa->GetLC_L1().FindParallelLine(x, y));
			GL::Vertex vIntersection = LineIntersection(sa->GetLC_R1(), sa->GetLC_L1());
			vertices[r1].Move(vIntersection.GetX(), vIntersection.GetY());
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
		if (*it > n)
			(*it)++;
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
		if ((*it) > n)
			(*it)--;
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
bool GL::Polygon::SetAngleFunction(int n)
{
	if (!isLooped)
		return false;
	if (CheckAngleIsSetToVertex(n))
	{
		DeleteVertFromAngleVector(n);
		return false;
	}

	int l1 = (n - 1 + vertices.size()) % vertices.size();
	int r1 = (n + 1) % vertices.size();
	if (isLooped || (n != 0 && (n + 1) != vertices.size()))
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
		float angle = acos((dot / (sqrt(x1*x1 + y1*y1)*sqrt(x2*x2 + y2*y2))))* 180.0 / PI;

		std::cin.clear();
		//cout << "angle : " << angle << "\n";
		//cout << "Enter angle\n";
		//float a;
		//cin >> a;
		//cout << "Your angle: " << a << " degrees\n\n";

		int l2 = (n - 2 + vertices.size()) % vertices.size();
		int r2 = (n + 2) % vertices.size();

		angles.push_back(n);
		SetAngle as = SetAngle(n, angle,
			LineCoefficients(v, v_l1), LineCoefficients(v_l1, GetVertex(l2)),
			LineCoefficients(v, v_r1), LineCoefficients(v_r1, GetVertex(r2)));
		setAngle.push_back(as);

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
		if ((*itr) == n)
		{
			angles.erase(itr++);
			return;
		}
		else
			++itr;
	}
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
		//return v_l1;
	}
	else
	{
		double x = (B2*C1 - B1*C2) / det;
		double y = (A1*C2 - A2*C1) / det;
		//double y = x*v4.GetY() / v4.GetX();
		cout << "x= " << x << " y= " << y << "\n";
		int y1 = round(y);
		return GL::Vertex(round(x), round(y));
	}
	return GL::Vertex(-1, -1);
}
bool GL::Polygon::CheckAngleIsSetToVertex(int n)
{
	for (auto& a : angles)
		if (a == n)
			return true;
	return false;
}

void GL::Polygon::UpdateLineParametries()
{
	for (auto &el : setAngle)
	{
		int n = el.GetVertexNumber();

		int l1 = (n - 1 + vertices.size()) % vertices.size();
		int r1 = (n + 1) % vertices.size();
		GL::Vertex v = GetVertex(n);
		GL::Vertex v_l1 = GetVertex(l1);
		GL::Vertex v_r1 = GetVertex(r1);

		//int x1 = v_l1.GetX() - v.GetX();	int x2 = v_r1.GetX() - v.GetX();
		//int y1 = v_l1.GetY() - v.GetY();	int y2 = v_r1.GetY() - v.GetY();
		//float dot = x1*x2 + y1*y2;
		//float angle = acos((dot / (sqrt(x1*x1 + y1*y1)*sqrt(x2*x2 + y2*y2))))* 180.0 / PI;

		int l2 = (n - 2 + vertices.size()) % vertices.size();
		int r2 = (n + 2) % vertices.size();

		el.SetLC_L1(GL::LineCoefficients(v, v_l1));
		el.SetLC_L2(GL::LineCoefficients(v_l1, GetVertex(l2)));
		el.SetLC_R1(GL::LineCoefficients(v, v_r1));
		el.SetLC_R2(GL::LineCoefficients(v_r1, GetVertex(r2)));
	}


}
