#include <GL/glut.h> 
#include <stdlib.h> 
#include "Manager.h"
#include "ExternVariables.h"
using namespace std;
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 300;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE );
	glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	glutCreateWindow("PolygonEditor");
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_HEIGHT, 0.0, WINDOW_WIDTH);

	glutMouseFunc(Manager::mouseFunc);
	glutPassiveMotionFunc(Manager::mousePassiveFunc);
	glutKeyboardUpFunc(Manager::keyboardFunc);

	glutMainLoop();
}