#include "Vertex.h"

GL::Vertex::Vertex()
{
	x = -1;
	y = -1;
}
GL::Vertex::~Vertex()
{
}
GL::Vertex::Vertex(int _x, int _y)
{
	x = _x;
	y = _y;
}
GL::Vertex::Vertex(GL::Point p)
{
	x = p.x;
	y = p.y;
}

void GL::Vertex::Draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
	glutPostRedisplay();
}
void GL::Vertex::HighlightVertex()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void GL::Vertex::UnhighlightVertex()
{
	Draw();
}

void GL::Vertex::Move(int _x, int _y)
{
	x = _x; 
	y = _y;
}

bool GL::Vertex::operator==(Vertex & v) const
{
	if ((x == v.GetX()) && (y == v.GetY()))
		return true;
	else
		return false;
}

bool GL::Vertex::operator!=(Vertex & v) const
{
	if ((x != v.GetX()) || (y != v.GetY()))
		return true;
	else
		return false;
}
