#include "global_variable.h"
#pragma region global_variable
using namespace std;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 600;
const int MENU_WIDTH = 350;

float vertexColorR = 0.13f;
float vertexColorG = 0.168f;
float vertexColorB = 0.18f;
float vertexHColorR = 1.0f;
float vertexHColorG = 0.0f;
float vertexHColorB = 0.0f;

extern float edgeColorR = 1.0f;
extern float edgeColorG = 1.0f;
extern float edgeColorB = 1.0f;
extern float edgeHColorR = 0.13f;
extern float edgeHColorG = 0.168f;
extern float edgeHColorB = 0.18f;

extern float polygonFillColorR = 0.33f;
extern float polygonFillColorG = 0.36f;
extern float polygonFillColorB = 0.35f;

extern float lightColorR = 1.0f;
extern float lightColorG = 1.0f;
extern float lightColorB = 1.0f;

extern bool isTexture = true;
extern bool isNormalMap = true;
extern bool isLightAnimated = false;

extern int lightRadius = 100;
extern float lightAngle = 0;
extern float lightStep = 0.2f;
extern float lightPositionX = 0;
extern float lightPositionY = 0;
extern int lightPositionZ = 100;

extern float lightVectorX = 0;
extern float lightVectorY = 0;
extern float lightVectorZ = 1;

extern float normalVectorX = 0;
extern float normalVectorY = 0;
extern float normalVectorZ = 1;

extern int textureNr = 0;
extern int normalMapNr=0;
#pragma endregion
#include "GL/glew.h"
#include "GL/freeglut.h"

#include "imgui\imgui.h"
#include "imgui_impl_glut.h"

#include <iostream>
#include "Manager.h"
using namespace std;

void init()
{
	glEnable(GL_MULTISAMPLE);
	glClearColor(0.447f, 0.565f, 0.604f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplGLUT_Init();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	//glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("PolygonEditor");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);

	Manager* m = Manager::getInstance();
	glutDisplayFunc(Manager::drawScene);
	glutPassiveMotionFunc(Manager::mousePassiveFunc);
	init();
	glutMainLoop();
	return 0;
}