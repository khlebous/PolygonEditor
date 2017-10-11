#include <GL/glut.h> 
#include <stdlib.h> 
#include "MouseManager.h"
#include "ExternVariables.h"
using namespace std;
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 300;

void display(void);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	glutCreateWindow("PolygonEditor");
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_HEIGHT, 0.0, WINDOW_WIDTH);

	glutDisplayFunc(display);

	glutMouseFunc(MouseManager::mouseFunc);
	glutPassiveMotionFunc(MouseManager::mousePassiveFunc);
	glutKeyboardFunc(MouseManager::loopPolygon);
	//glutIdleFunc(idle);
	glutMainLoop();
}

void display(void)
{
}
