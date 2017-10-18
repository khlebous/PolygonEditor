#include"GraphicsLibrary.h"

void GL::DrawPolygon(GL::Polygon * p, int highlightV, int highlightE)
{
	glClear(GL_COLOR_BUFFER_BIT);


	vector<GL::Vertex> vertices = p->GetVertices();
	size_t i = 0;
	//TODO delete when 1 pkt
	for (; i < vertices.size() - 1; i++)
	{
		GL::DrawVertice(vertices[i]);
		GL::DrawEdge(vertices[i], vertices[i + 1]);
	}
	DrawVertice(vertices[i]);
	if (p->IsLooped())
		GL::DrawEdge(vertices[i], vertices[0]);

	list<int> vEdges = p->GetVEdges();
	for (auto it = vEdges.begin(); it != vEdges.end(); it++)
		GL::DrawVertSign(p->GetVertex(*it), p->GetVertex(((*it) + 1) % vertices.size()));
	list<int> hEdges = p->GetHEdges();
	for (auto it = hEdges.begin(); it != hEdges.end(); it++)
		GL::DrawHorizSign(p->GetVertex(*it), p->GetVertex(((*it) + 1) % vertices.size()));
	for (auto const &a : p->GetAngles()) 
		GL::DrawAngleSign(p->GetVertex(a.first));

	if (highlightV != -1)
		GL::DrawHighlightVertice(p->GetVertex(highlightV));
	else if (highlightE != -1)
		GL::DrawHighlightEdge(p->GetVertex(highlightE), p->GetVertex((highlightE + 1) % vertices.size()));

	glutSwapBuffers();
}

// TODO more univesal
void GL::SetPixel(int x, int y, float size)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
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
	//TODO another one
	int x1 = v1.GetX();
	int y1 = v1.GetY();
	int x2 = v2.GetX();
	int y2 = v2.GetY();
	vector<GL::Point> edge;

	// Bresenham's line algorithm
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	float dx = x2 - x1;
	float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	int maxX = (int)x2;

	for (int x = (int)x1; x < maxX; x++)
	{
		if (steep)
			edge.push_back(GL::Point(y, x));
		else
			edge.push_back(GL::Point(x, y));

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (GL::Point& p : edge)
		glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
	//glutSwapBuffers();

}
void GL::DrawHighlightEdge(GL::Vertex v1, GL::Vertex v2)
{
	//TODO another one
	int x1 = v1.GetX();
	int y1 = v1.GetY();
	int x2 = v2.GetX();
	int y2 = v2.GetY();
	vector<GL::Point> edge;

	// Bresenham's line algorithm
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	float dx = x2 - x1;
	float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	int maxX = (int)x2;

	for (int x = (int)x1; x < maxX; x++)
	{
		if (steep)
			edge.push_back(GL::Point(y, x));
		else
			edge.push_back(GL::Point(x, y));

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (GL::Point& p : edge)
		glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
	//glutSwapBuffers();

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
	glPointSize(6);
	glBegin(GL_POINTS);
	glVertex2i(v1.GetX(), v1.GetY());
	glEnd();
	glFlush();
}
