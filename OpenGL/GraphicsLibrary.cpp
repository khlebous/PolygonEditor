#include"GraphicsLibrary.h"

void GL::DrawPolygon(GL::Polygon * p)
{
	glClear(GL_COLOR_BUFFER_BIT);
	vector<GL::Vertice> vertices = p->GetVertices();
	size_t i = 0;
	for (; i < vertices.size()-1; i++)
	{
		GL::DrawVertice(vertices[i]);
		GL::DrawEdge(vertices[i], vertices[i + 1]);
	}
	DrawVertice(vertices[i]);
	if (p->IsLooped())
		GL::DrawEdge(vertices[i], vertices[0]);
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

void GL::DrawVertice(GL::Vertice v)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(v.GetX(), v.GetY());
	glEnd(); 
	glFlush();
	//glutSwapBuffers();
}

void GL::DrawEdge(GL::Vertice v1, GL::Vertice v2)
{
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
