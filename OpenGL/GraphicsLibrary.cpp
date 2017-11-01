#include"GraphicsLibrary.h"
void GL::DrawPolygon(GL::Polygon * p, GL::Polygon * p1, int highlightV, int highlightE)
{
	glClear(GL_COLOR_BUFFER_BIT);
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

	list<int> vEdges = p->GetVEdges();
	for (auto it = vEdges.begin(); it != vEdges.end(); it++)
		GL::DrawVertSign(p->GetVertex(*it), p->GetVertex(((*it) + 1) % vertices.size()));
	list<int> hEdges = p->GetHEdges();
	for (auto it = hEdges.begin(); it != hEdges.end(); it++)
		GL::DrawHorizSign(p->GetVertex(*it), p->GetVertex(((*it) + 1) % vertices.size()));
	for (auto const &a : p->GetAngles())
		GL::DrawAngleSign(p->GetVertex(a.first));

	list<int> vEdgesTmp = p->GetVEdgesTmp();
	for (auto it = vEdgesTmp.begin(); it != vEdgesTmp.end(); it++)
		GL::DrawVertSign(p->GetVertex(*it), p->GetVertex(((*it) + 1) % vertices.size()));
	list<int> hEdgesTmp = p->GetHEdgesTmp();
	for (auto it = hEdgesTmp.begin(); it != hEdgesTmp.end(); it++)
		GL::DrawHorizSign(p->GetVertex(*it), p->GetVertex(((*it) + 1) % vertices.size()));

	if (highlightV != -1)
		GL::DrawHighlightVertice(p->GetVertex(highlightV));
	else if (highlightE != -1)
		GL::DrawHighlightEdge(p->GetVertex(highlightE), p->GetVertex((highlightE + 1) % vertices.size()));

	//draw second
	if (p1 != nullptr)
	{
		vector<GL::Vertex> vertices1 = p1->GetVertices();
		int i = 0;
		auto size = (int)vertices1.size() - 1;
		for (; i < size; i++)
		{
			GL::DrawVertice(vertices1[i]);
			GL::DrawEdge(vertices1[i], vertices1[i + 1]);
		}
		if (size != -1)
		{
			DrawVertice(vertices1[i]);
			if (p1->IsLooped())
				GL::DrawEdge(vertices1[i], vertices1[0]);
		}
	}

	glutSwapBuffers();
}

void GL::DrawVertice(GL::Vertex v)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(v.GetX(), v.GetY());
	glEnd();
	glFlush();
}
void GL::DrawHighlightVertice(GL::Vertex v)
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(v.GetX(), v.GetY());
	glEnd();
	glFlush();
}

void GL::DrawEdge(GL::Vertex v1, GL::Vertex v2)
{
	vector<GL::Point> edge = CalculateLinePixels(v1, v2);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (GL::Point& p : edge)
		glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
}
void GL::DrawHighlightEdge(GL::Vertex v1, GL::Vertex v2)
{
	vector<GL::Point> edge = CalculateLinePixels(v1, v2);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (GL::Point& p : edge)
		glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
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
	glFlush();
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
	glFlush();
}
void GL::DrawAngleSign(GL::Vertex v1)
{
	glColor3f(0.0f, 0.3f, 1.0f);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(v1.GetX(), v1.GetY());
	glEnd();
	glFlush();
}
