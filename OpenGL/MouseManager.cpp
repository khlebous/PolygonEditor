#include "ExternVariables.h"
#include "MouseManager.h"
#include "GraphicsLibrary.h"
#include <GL/glut.h> 
#include <stdlib.h> 

MouseManager* MouseManager::instance = NULL;

MouseManager::MouseManager()
{
	polygon = new GL::Polygon;
}

MouseManager* MouseManager::getInstance()
{
	if (!instance)
		instance = new MouseManager;
	return instance;
	//	return nullptr;
	//return nullptr;
}

MouseManager::~MouseManager()
{
	polygon->~Polygon();
}

void MouseManager::mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{

		glColor3f(1.0f, 1.0f, 1.0f);
		glPointSize(1);
		glBegin(GL_POINTS);
		glVertex2i(x, WINDOW_WIDTH - y);
		glEnd();

		/*POINT ptA;
		ptA.x = x;
		ptA.y = WINDOW_WIDTH - y;*/
		//polygon.AddVertice(x, WINDOW_WIDTH - y);
		//Drawline(polygon.GetPoint(polygon.VerticesCount() - 2), polygon.GetPoint(polygon.VerticesCount() - 1));
		//glFlush();
	}
}

void MouseManager::mouse2(int button, int state, int x, int y)
{
	GL::Polygon* polygon = getInstance()->polygon;

	//
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2i(x, WINDOW_WIDTH - y);
	glEnd();

	polygon->AddVertice(x, WINDOW_WIDTH - y);
	//if (polygon->VerticesCount() > 1)
//Drawline(polygon->GetPoint(polygon->VerticesCount() - 2), polygon->GetPoint(polygon->VerticesCount() - 1));
	glFlush();
}