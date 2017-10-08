#include <GL/glut.h> 
#include <stdlib.h> 
#include "MouseManager.h"
#include "ExternVariables.h"
using namespace std;
const int WINDOW_HEIGHT = 640;
const int WINDOW_WIDTH = 320;
void display(void)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (int i = 0; i < 100; i++)
	{
		glVertex2i(i, i);
	}
	glEnd();

	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	
}
static void mouse2(int button, int state, int x, int y)
{

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	glutCreateWindow("Randomly generated points");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_HEIGHT, 0.0, WINDOW_WIDTH);

	glutDisplayFunc(display);

	glutMouseFunc(MouseManager::mouse2);
	//glutIdleFunc(idle);
	glutMainLoop();
}
