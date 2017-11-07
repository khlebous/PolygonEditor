#include"GraphicsLibrary.h"
#include <algorithm>  
#include "AET.h"
#include "global_variable.h"

const int VERTEX_POINT_SIZE = 6;
const int EDGE_POINT_SIZE = 1;

struct less_than_key
{
	inline bool operator() (const GL::Vertex& struct1, const GL::Vertex& struct2)
	{
		return (struct1.GetY() < struct2.GetY());
	}
};
void GL::FillPolygon(GL::Polygon * p)
{
	glColor3f(polygonFillColorR, polygonFillColorG, polygonFillColorB);
	glPointSize(1);
	glBegin(GL_POINTS);
	vector<GL::Vertex> v = p->GetVertices();
	int size = v.size();
	for (int i = 0; i < size; i++)
		v[i].nr = i;
	std::sort(v.begin(), v.end(), less_than_key());
	int* indexes = new int[size];
	for (int i = 0; i < v.size(); i++)
		indexes[i] = v[i].nr;
	v = p->GetVertices();
	for (int i = 0; i < size; i++)
		v[i].nr = i;
	int ymin = v[indexes[0]].GetY();
	int ymax = v[indexes[size - 1]].GetY();
	vector<GL::AET> AET = vector<GL::AET>();
	int vIndex = 0;
	for (int k = ymin; k <= ymax; k++)
	{
		vector<GL::Vertex> vPrev = vector<GL::Vertex>();
		while (v[indexes[vIndex]].GetY() == k - 1)
			vPrev.push_back(v[indexes[vIndex++]]);
		for (int i = 0; i < vPrev.size(); i++)
		{
			GL::Vertex v_prev = v[(vPrev[i].nr - 1 + size) % size];
			if (v_prev.GetY() > vPrev[i].GetY())
				AET.push_back(GL::AET(v_prev, vPrev[i]));
			else if (v_prev.GetY() < vPrev[i].GetY())
			{
				int j = 0;
				for (j = 0; j < AET.size(); j++)
				{
					if ((v_prev == AET[j].v1) && (vPrev[i] == AET[j].v2) ||
						(v_prev == AET[j].v2) && (vPrev[i] == AET[j].v1))
						break;
				}
				AET.erase(AET.begin() + j);
			}

			GL::Vertex v_next = v[(vPrev[i].nr + 1) % size];
			if (v_next.GetY() > vPrev[i].GetY())
				AET.push_back(GL::AET(v_next, vPrev[i]));
			else if (v_next.GetY() < vPrev[i].GetY())
			{
				int j = 0;
				for (j = 0; j < AET.size(); j++)
				{
					if (((v_next == AET[j].v1) && (vPrev[i] == AET[j].v2)) ||
						((v_next == AET[j].v2) && (vPrev[i] == AET[j].v1)))
						break;
				}
				AET.erase(AET.begin() + j);
			}
		}
		vPrev.clear();
		std::sort(AET.begin(), AET.end());
		for (int l = 0; l < AET.size(); l += 2)
		{
			int cos = AET[l].x;
			while (cos <= (int)round(AET[l + 1].x))
				glVertex2i((int)round(cos++), (int)round(k));

		}
		for (int l = 0; l < AET.size(); l++)
		{
			AET[l].x += AET[l].m;
		}
	}
	glEnd();
	glFlush();
	//glColor3f(1.0f, 1.0f, 1.0f);
	glColor3f(vertexColorR, vertexColorG, vertexColorB);
	glPointSize(VERTEX_POINT_SIZE);
	glBegin(GL_POINTS);
	for (int q = 0; q < size; q++)
		glVertex2i(v[q].GetX(), v[q].GetY());
	glEnd();
	//glFlush();
	delete indexes;
}

void GL::DrawPolygons(vector<GL::Polygon*> p, int highlightP, int highlightV, int highlightE)
{
	//glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < p.size(); i++)
	{
		if (p[i]->IsLooped())
			GL::FillPolygon(p[i]);
		else
			GL::DrawPolygon(p[i]);
	}

	if (highlightP != -1)
	{
		if (highlightV != -1)
			GL::DrawHighlightVertice(p[highlightP]->GetVertex(highlightV));
		else if (highlightE != -1)
			GL::DrawHighlightEdge(p[highlightP]->GetVertex(highlightE),
				p[highlightP]->GetVertex(highlightE + 1));
	}

	//glutSwapBuffers();
}
void GL::DrawPolygon(GL::Polygon * p)
{
	vector<GL::Vertex> vertices = p->GetVertices();
	int i = 0;
	auto size = (int)vertices.size() - 1;
	for (; i < size; i++)
	{
		GL::DrawVertice(vertices[i]);
		GL::DrawEdge(vertices[i], vertices[i + 1]);
	}
	if (size != -1)
	{
		DrawVertice(vertices[i]);
		if (p->IsLooped())
			GL::DrawEdge(vertices[i], vertices[0]);
	}

	/*list<int> vEdges = p->GetVEdges();
	for (auto it = vEdges.begin(); it != vEdges.end(); it++)
		GL::DrawVertSign(p->GetVertex(*it), p->GetVertex(((*it) + 1) % vertices.size()));
	list<int> hEdges = p->GetHEdges();
	for (auto it = hEdges.begin(); it != hEdges.end(); it++)
		GL::DrawHorizSign(p->GetVertex(*it), p->GetVertex(((*it) + 1) % vertices.size()));
	for (auto const &a : p->GetAngles())
		GL::DrawAngleSign(p->GetVertex(a.first));
	*/
	/*list<int> vEdgesTmp = p->GetVEdgesTmp();
	for (auto it = vEdgesTmp.begin(); it != vEdgesTmp.end(); it++)
		GL::DrawVertSign(p->GetVertex(*it), p->GetVertex(((*it) + 1) % vertices.size()));
	list<int> hEdgesTmp = p->GetHEdgesTmp();
	for (auto it = hEdgesTmp.begin(); it != hEdgesTmp.end(); it++)
		GL::DrawHorizSign(p->GetVertex(*it), p->GetVertex(((*it) + 1) % vertices.size()));
*/

}

void GL::DrawVertice(GL::Vertex v)
{
	glColor3f(vertexColorR, vertexColorG, vertexColorB);
	glPointSize(VERTEX_POINT_SIZE);
	glBegin(GL_POINTS);
	glVertex2i(v.GetX(), v.GetY());
	glEnd();
}
void GL::DrawHighlightVertice(GL::Vertex v)
{
	glColor3f(vertexHColorR, vertexHColorG, vertexHColorB);
	glPointSize(VERTEX_POINT_SIZE);
	glBegin(GL_POINTS);
	glVertex2i(v.GetX(), v.GetY());
	glEnd();
}

void GL::DrawEdge(GL::Vertex v1, GL::Vertex v2)
{
	vector<GL::Point> edge = CalculateLinePixels(v1, v2);
	glColor3f(edgeColorR, edgeColorG, edgeColorB);
	glPointSize(EDGE_POINT_SIZE);
	glBegin(GL_POINTS);
	for (GL::Point& p : edge)
		glVertex2i(p.x, p.y);
	glEnd();
}
void GL::DrawHighlightEdge(GL::Vertex v1, GL::Vertex v2)
{
	vector<GL::Point> edge = CalculateLinePixels(v1, v2);
	glColor3f(edgeHColorR, edgeHColorG, edgeHColorB);
	glPointSize(EDGE_POINT_SIZE);
	glBegin(GL_POINTS);
	for (GL::Point& p : edge)
		glVertex2i(p.x, p.y);
	glEnd();
}
vector<GL::Point> GL::CalculateLinePixels(GL::Vertex v1, GL::Vertex v2)
{
	vector<GL::Point> line;
	int x1 = v1.GetX();
	int y1 = v1.GetY();
	int x2 = v2.GetX();
	int y2 = v2.GetY();
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = dx - dy;

	line.push_back(GL::Point(x2, y2));
	while (x1 != x2 || y1 != y2)
	{
		line.push_back(GL::Point(x1, y1));
		int error2 = error * 2;
		if (error2 > -dy)
		{
			error -= dy;
			x1 += signX;
		}
		if (error2 < dx)
		{
			error += dx;
			y1 += signY;
		}
	}
	return line;
}

void GL::DrawVertSign(GL::Vertex v1, GL::Vertex v2)
{
	int x = (v1.GetX() + v2.GetX()) / 2;
	int y = (v1.GetY() + v2.GetY()) / 2 - 8;
	glColor3f(1.0f, 0.5f, 0.0f);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int j = 0; j < 4; j++)
		glVertex2i(x, y + j * 4);
	glEnd();
}
void GL::DrawHorizSign(GL::Vertex v1, GL::Vertex v2)
{
	int x = (v1.GetX() + v2.GetX()) / 2 - 8;
	int y = (v1.GetY() + v2.GetY()) / 2;
	glColor3f(1.0f, 0.5f, 0.0f);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int j = 0; j < 4; j++)
		glVertex2i(x + j * 4, y);
	glEnd();
}
void GL::DrawAngleSign(GL::Vertex v1)
{
	glColor3f(0.0f, 0.3f, 1.0f);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(v1.GetX(), v1.GetY());
	glEnd();
}
