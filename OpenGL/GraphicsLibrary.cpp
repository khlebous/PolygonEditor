#include"GraphicsLibrary.h"

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
