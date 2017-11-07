#include "GL/glew.h"
#include "GL/freeglut.h"

#include "IMGUI/imgui.h"
#include "imgui_impl_glut.h"
#include <iostream>

#include <stdlib.h> 
#include "Manager.h"
#include "ExternVariables.h"
using namespace std;

const int WINDOW_HEIGHT = 1280;
const int WINDOW_WIDTH = 720;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);

	//glutInitDisplayMode(GLUT_DOUBLE );
	glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	glutCreateWindow("PolygonEditor");
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_HEIGHT, 0.0, WINDOW_WIDTH);

	glutMouseFunc(Manager::mouseFunc);
	glutPassiveMotionFunc(Manager::mousePassiveFunc);
	glutKeyboardUpFunc(Manager::keyboardFunc);
	glutDisplayFunc(display);
	
	init();

	glutMainLoop();
}