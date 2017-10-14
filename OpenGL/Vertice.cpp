#include "Vertice.h"

GL::Vertice::Vertice()
{
	x = -1;
	y = -1;
}
GL::Vertice::~Vertice()
{
}
GL::Vertice::Vertice(int _x, int _y)
{
	x = _x;
	y = _y;
}
GL::Vertice::Vertice(GL::Point p)
{
	x = p.x;
	y = p.y;
}

void GL::Vertice::Draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
	glutPostRedisplay();
}
void GL::Vertice::HighlightVertice()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void GL::Vertice::UnhighlightVertice()
{
	Draw();
}

void GL::Vertice::Move(int _x, int _y)
{
	//glColor3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glPointSize(4);
	glBegin(GL_POINTS);
	//glVertex2i(x, y);
	glVertex2i(_x, _y);
	glEnd();
	glFlush();
}

bool GL::Vertice::operator==(Vertice & v) const
{
	if ((x == v.GetX()) && (y == v.GetY()))
		return true;
	else
		return false;
}

bool GL::Vertice::operator!=(Vertice & v) const
{
	if ((x != v.GetX()) || (y != v.GetY()))
		return true;
	else
		return false;
}
