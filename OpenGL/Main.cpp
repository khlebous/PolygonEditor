﻿//#include <GL/glut.h> 
//#include "imgui\imgui.h"
//#include <stdlib.h> 
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

extern float edgeColorR= 1.0f;
extern float edgeColorG= 1.0f;
extern float edgeColorB= 1.0f;
extern float edgeHColorR = 0.13f;
extern float edgeHColorG = 0.168f;
extern float edgeHColorB = 0.18f;

extern float polygonFillColorR = 0.33f;
extern float polygonFillColorG = 0.36f;
extern float polygonFillColorB = 0.35f;
#pragma endregion

// ImGui - standalone example application for Glut + OpenGL, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "IMGUI/imgui.h"
#include "imgui_impl_glut.h"

#include <iostream>
#include "Manager.h"
using namespace std;

//unsigned int screenWidth = 1200;
//unsigned int screenHeight = 600;
bool show_test_window = true;
bool show_another_window = false;

void drawGUI()
{
	ImGui_ImplGLUT_NewFrame(WINDOW_WIDTH, WINDOW_HEIGHT);

	// 1. Show a simple window
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
	{
		static ImVec4 color = ImColor(114, 144, 154, 200);
		static bool hdr = false;
		static bool alpha_preview = true;
		static bool alpha_half_preview = false;
		static bool options_menu = true;
		int misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
		static float f = 0.0f;
		ImGui::SetWindowPos(ImVec2(0, 0));
		ImGui::SetWindowSize(ImVec2(300, 600));
		ImGui::Text("Color of light source");
		ImGui::ColorEdit3("MyColor##1", (float*)&color, misc_flags);
		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		//if (ImGui::Button("Settings Window")) show_test_window ^= 1;
		//if (ImGui::Button("Another Window")) show_another_window ^= 1;
		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	// 2. Show another simple window, this time using an explicit Begin/End pair
	/*if (show_another_window)
	{
		ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello");
		ImGui::End();
	}*/

	// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	//if (show_test_window)
	{
		ImGui::SetNextWindowPos(ImVec2(0, 100));
		ImGui::SetNextWindowSize(ImVec2(300, 500));
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}

	ImGui::Render();
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// add code here to draw scene objects

	// draw gui
	drawGUI();

	glutSwapBuffers();
}
bool keyboardEvent(unsigned char nChar, int nX, int nY)
{
	ImGuiIO& io = ImGui::GetIO();

	io.AddInputCharacter(nChar);

	return true;
}
bool mouseEvent(int button, int state, int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	if (state == GLUT_DOWN && (button == GLUT_LEFT_BUTTON))
		io.MouseDown[0] = true;
	else
		io.MouseDown[0] = false;

	if (state == GLUT_DOWN && (button == GLUT_RIGHT_BUTTON))
		io.MouseDown[1] = true;
	else
		io.MouseDown[1] = false;

	// Wheel reports as button 3(scroll up) and button 4(scroll down)
	if (state == GLUT_DOWN && button == 3) // It's a wheel event
		io.MouseWheel = 1.0;
	else
		io.MouseWheel = 0.0;

	if (state == GLUT_DOWN && button == 4) // It's a wheel event
		io.MouseWheel = -1.0;
	else
		io.MouseWheel = 0.0;


	return true;
}
//void reshape(int w, int h)
//{
//	WINDOW_WIDTH = w;
//	screenHeight = h;
//
//	glViewport(0, 0, screenWidth, screenHeight);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	if (screenWidth > screenHeight)
//	{
//		float fWidth(screenWidth / screenHeight);
//		float fOffset((fWidth - 1.0f)*0.5f);
//		gluOrtho2D(0 - fOffset, fWidth - fOffset, 1.0f, 0.0f);
//	}
//	else
//	{
//		float fHeight(screenWidth / screenHeight);
//		float fOffset((fHeight - 1.0f)*0.5f);
//		gluOrtho2D(0, 1.0f, fHeight - fOffset, 0 - fOffset);
//	}
//	glMatrixMode(GL_MODELVIEW);
//}
void keyboardCallback(unsigned char nChar, int x, int y)
{
	if (keyboardEvent(nChar, x, y))
	{
		glutPostRedisplay();
	}
}
void mouseCallback(int button, int state, int x, int y)
{
	if (mouseEvent(button, state, x, y))
	{
		glutPostRedisplay();
	}
}
void mouseDragCallback(int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	glutPostRedisplay();
}
void mouseMoveCallback(int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	glutPostRedisplay();
}

// initialize ogl and imgui
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
	//glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("PolygonEditor");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
	Manager* m = Manager::getInstance();

	// callback
	//glutDisplayFunc(drawScene);
	glutDisplayFunc(Manager::drawScene);
	glutPassiveMotionFunc(Manager::mousePassiveFunc);
	//glutReshapeFunc(reshape);
	//glutKeyboardFunc(keyboardCallback);

	//glutDisplayFunc(drawScene);

	/**/

	init();
	glutMainLoop();

	return 0;
}




