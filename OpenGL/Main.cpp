#include <GL/glut.h> 
#include <stdlib.h> 
#include "MouseManager.h"
#include "ExternVariables.h"
using namespace std;
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 300;

void idle(void);
void display(void);
void mouse(int button, int state, int x, int y);
void mouse2(int x, int y);
void initGL() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE );
	glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	glutCreateWindow("PolygonEditor");

	glClearColor(0, 0, 0, 0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//init

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_HEIGHT, 0.0, WINDOW_WIDTH);

	glutDisplayFunc(display);
	//glutMotionFunc(mouse2);
	
	glutMouseFunc(MouseManager::mouseFunc);
	//glutMouseFunc(mouse);
	
	glutPassiveMotionFunc(MouseManager::mousePassiveFunc);
	//glutPassiveMotionFunc(mouse2);
	
	glutKeyboardFunc(MouseManager::loopPolygon);
	
	//glutIdleFunc(idle);
	initGL();
	glutMainLoop();
}

int x=-1; int y=-1; bool isDisp = false;
void mouse(int button, int state, int _x, int _y)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		isDisp = true;
		glutIdleFunc(idle);
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
	{
		isDisp = false;
		glutIdleFunc(NULL);
	}
}
void mouse2(int _x, int _y)
{
	x = _x;
	y = WINDOW_WIDTH - _y;
}
void idle(void)
{
	if (isDisp)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 1.0f);
		glPointSize(4);
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		glFlush();
		glutSwapBuffers();
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		glutSwapBuffers();
	}

}

void display(void)
{
	/*if (isDisp)
	{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 1.0f);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
	glutSwapBuffers();
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		glutSwapBuffers();
	}*/
}
