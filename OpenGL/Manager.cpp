#include "GL/glew.h"
#include "GL/freeglut.h"

#include "IMGUI/imgui.h"
#include "imgui_impl_glut.h"

#include "global_variable.h"
#include "Manager.h"
#include "GraphicsLibrary.h"
#include <iostream>
using namespace std;
bool show_test_window2 = true;
int listbox_item_current = 0;

Manager* Manager::instance = NULL;

Manager::Manager()
{
	polygons = vector<GL::Polygon*>();
	GL::Polygon* pp = new GL::Polygon();
	pp->AddVertex(500, 200);
	pp->AddVertex(300, 300);
	pp->AddVertex(400, 500);
	polygons.push_back(pp);
	highlightVertice = -1;
	highlightEdge = -1;
	highlightPolygon = -1;

	_x = -1;
	_y = -1;
	_nr = -1;
}

Manager* Manager::getInstance()
{
	if (!instance)
		instance = new Manager;
	return instance;
}
Manager::~Manager()
{
	for (auto &p : polygons)
		p->~Polygon();
	polygons.clear();
	//polygon->~Polygon();
}

void Manager::mouseFunc(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
	{
		glutMotionFunc(NULL);
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		y = WINDOW_HEIGHT - y;
		glutMotionFunc(Manager::motionFuncLeft);
		Manager* mm = getInstance();
		vector<GL::Polygon*> p = mm->polygons;

		//loop
		if (mm->highlightVertice == 0)
		{
			if (mm->polygons[mm->highlightPolygon]->Loop())
			{
				//GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, -1);
				drawScene();
				return;
			}
		}
		//move polygon
		for (int i = 0; i < p.size(); i++)
		{
			if (p[i]->IsInside(x, y))
			{
				mm->_nr = i;
				break;
			}
			mm->_nr = -1;
		}
		if (-1 != mm->_nr)
		{
			glutMotionFunc(Manager::motionFuncRight);
			mm->_x = x;
			mm->_y = y;
		}
		else if (mm->highlightVertice == -1)
			mm->NewVertexAndEdge(x, y);
		else
			mm->polygons[mm->highlightPolygon]->MoveVertex(mm->highlightVertice, x, y);
	}
}
void Manager::mousePassiveFunc(int x, int y)
{
	y = WINDOW_HEIGHT - y;
	Manager* mm = getInstance();
	if ((x < WINDOW_WIDTH - MENU_WIDTH))
	{
		if ((!mm->drawingArea))
		{
			mm->drawingArea = true;
			glutMouseFunc(Manager::mouseFunc);
			glutKeyboardUpFunc(Manager::keyboardFunc);
		}
		if (!mm->CheckVertices(x, y))
			mm->CheckEdges(x, y);
	}
	else if ((x >= WINDOW_WIDTH - MENU_WIDTH) && (mm->drawingArea))
	{
		mm->drawingArea = false;
		glutMouseFunc(mouseCallback);
		glutMotionFunc(mouseDragCallback);
		glutKeyboardFunc(keyboardCallback);
		glutPassiveMotionFunc(mouseMoveCallback);
	}

}
void Manager::keyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27://esc
		exit(0);
		break;
	case 'a': // add new vertex
	{
		Manager* mm = getInstance();
		if (mm->highlightEdge != -1)
		{
			GL::Polygon* polygon = mm->polygons[mm->highlightPolygon];
			polygon->AddVertAtEdge(mm->highlightEdge, x, WINDOW_HEIGHT - y);
			//GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
			drawScene();
		}
		break;
	}
	case 'd': //delete vertex
	{
		Manager* mm = getInstance();
		if (mm->highlightVertice != -1)
		{
			GL::Polygon* polygon = mm->polygons[mm->highlightPolygon];
			polygon->DeleteVert(mm->highlightVertice);
			mm->highlightVertice = -1;
			//GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
			drawScene();
		}
		break;
	}
	case 'l': // loop polygon
	{
		Manager* mm = getInstance();
		//GL::Polygon* polygon = mm->polygon;
		//GL::Polygon* polygon2 = mm->polygon2;
		GL::Polygon* p = mm->polygons[mm->polygons.size() - 1];
		if (!p->IsLooped())
			p->Loop();
		//GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
		drawScene();
		break;
	}
	case 'v': // try to make edge vertical
	{
		Manager* mm = getInstance();
		if (mm->highlightEdge != -1)
		{
			GL::Polygon* p = mm->polygons[mm->highlightPolygon];
			p->MakeEdgeVertical(mm->highlightEdge);
			//GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
			drawScene();
		}
		break;
	}
	case 'h': // try to make edge horizontal
	{
		Manager* mm = getInstance();
		if (mm->highlightEdge != -1)
		{
			GL::Polygon* polygon = mm->polygons[mm->highlightPolygon];
			polygon->MakeEdgeHorizontal(mm->highlightEdge);
			//GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
			drawScene();
		}
		break;
	}
	case 's': // set angle
	{
		Manager* mm = getInstance();
		if (mm->highlightVertice != -1)
			if (mm->polygons[mm->highlightPolygon]->SetAngleFunction(mm->highlightVertice))
				//	GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
				drawScene();
		break;
	}
	}
}
void Manager::motionFuncLeft(int _x, int _y)
{
	Manager* mm = getInstance();
	if (mm->highlightVertice != -1)
	{
		GL::Polygon* p = mm->polygons[mm->highlightPolygon];
		p->MoveVertex(mm->highlightVertice, _x, WINDOW_HEIGHT - _y);
	}
	//GL::DrawPolygons(mm->polygons, -1, -1, -1);
	drawScene();
}
void Manager::motionFuncRight(int x, int y)
{
	y = WINDOW_HEIGHT - y;
	Manager* mm = getInstance();
	mm->polygons[mm->_nr]->MovePolygon(x - mm->_x, y - mm->_y);
	mm->_x = x;
	mm->_y = y;
	//GL::DrawPolygons(mm->polygons, -1, -1, -1);
	drawScene();
}
void Manager::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// add code here to draw scene objects

	// draw gui
	Manager* mm = getInstance();
	GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
	mm->drawGUI();

	glutSwapBuffers();
}

//=====================================================
//private
void Manager::NewVertexAndEdge(int x, int y)
{
	GL::Polygon *p;
	if (polygons.size() == 0)
		p = nullptr;
	else
		p = polygons[polygons.size() - 1];
	if (p != nullptr)
	{
		/*if ((p->VertCount() > 0) && (highlightVertice == 0) && (highlightPolygon == (polygons.size() - 1)))
		{
			if (p->Loop())
			{
				GL::DrawPolygons(polygons, -1, -1, -1);
				return;
			}
		}
		else */
		if (!(p->IsLooped()))
		{
			p->AddVertex(x, y);
			//GL::DrawPolygons(polygons, -1, -1, -1);
			glutPostRedisplay();
			return;
		}
	}
	//else
	//{
	GL::Polygon* pp = new GL::Polygon();
	polygons.push_back(pp);
	polygons[polygons.size() - 1]->AddVertex(x, y);
	//}

	/*if (polygon->CheckMouseNearVertice(x, y) != -1)
	{
		return;
	}*/

	//if (polygon->VertCount() > 1)
	GL::DrawPolygons(polygons, -1, -1, -1);
	//drawScene();
	glutPostRedisplay();
}
bool Manager::CheckVertices(int x, int y)
{
	int v = -1;
	int p = -1;
	for (int i = 0; i < polygons.size(); i++)
	{
		v = polygons[i]->CheckMouseNearVertice(x, y);
		if (-1 != v)
		{
			p = i;
			break;
		}
	}
	if (v == -1)
	{
		if (highlightVertice != -1)
		{
			highlightVertice = -1;
			highlightPolygon = -1;
		}
		//GL::DrawPolygons(polygons, highlightPolygon, highlightVertice, highlightEdge);
		glutPostRedisplay();
		return false;
	}
	if ((highlightVertice != v) || (highlightPolygon != p))
	{
		highlightVertice = v;
		glutPostRedisplay();
		highlightPolygon = p;
		//GL::DrawPolygons(polygons, highlightPolygon, highlightVertice, highlightEdge);
	}
	return true;
}
void Manager::CheckEdges(int x, int y)
{
	int e = -1;
	int p = -1;
	for (int i = 0; i < polygons.size(); i++)
	{
		if (-1 != (e = polygons[i]->CheckMouseNearEdge(x, y)))
		{
			p = i;
			break;
		}
	}
	if (e == -1)
	{
		if (highlightEdge != -1)
		{
			highlightEdge = -1;
			highlightPolygon = -1;
			GL::DrawPolygons(polygons, highlightPolygon, highlightVertice, highlightEdge);
		}
	}
	else if ((highlightEdge != e) || (highlightPolygon != p))
	{
		highlightEdge = e;
		highlightPolygon = p;
		GL::DrawPolygons(polygons, highlightPolygon, highlightVertice, highlightEdge);
	}
}

void Manager::drawGUI()
{
	ImGui_ImplGLUT_NewFrame(WINDOW_WIDTH, WINDOW_HEIGHT);

	// 1. Show a simple window
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
	{
		ImGui::SetWindowPos(ImVec2(WINDOW_WIDTH - MENU_WIDTH, 0));
		ImGui::SetWindowSize(ImVec2(MENU_WIDTH, WINDOW_HEIGHT));

		static ImVec4 fillColor = ImColor((int)(polygonFillColorR * 255), (int)(polygonFillColorG * 255), (int)(polygonFillColorB * 255));
		static bool hdr = false;
		static bool alpha_preview = true;
		static bool alpha_half_preview = false;
		static bool options_menu = true;
		int misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
		static float f = 0.0f;
		ImGui::Text("Kolor zrodla swiata");
		static ImVec4 lightColor = ImColor((int)(lightColorR * 255), (int)(lightColorG * 255), (int)(lightColorB * 255));
		if (ImGui::ColorEdit3("##2", (float*)&lightColor, misc_flags))
		{
			lightColorR = lightColor.x;
			lightColorG = lightColor.y;
			lightColorB = lightColor.z;
		}
		ImGui::Text("------------------------------------------------");
		ImGui::Text("Wektor do zrodla switala");
		static int rb1 = 0;
		ImGui::RadioButton("Staly [0,0,1]", &rb1, 0);
		ImGui::RadioButton("Swiatlo animowane TODO", &rb1, 1);
		ImGui::Text("------------------------------------------------");
		ImGui::Text("Kolor obiektu");
		static int rb2 = 0;
		if (ImGui::RadioButton("Staly kolor", &rb2, 0))
			isTexture = false;
		ImGui::SameLine();
		if (ImGui::ColorEdit3("##1", (float*)&fillColor, misc_flags))
		{
			polygonFillColorR = fillColor.x;
			polygonFillColorG = fillColor.y;
			polygonFillColorB = fillColor.z;
		}
		if (ImGui::RadioButton("Z tekstury", &rb2, 1))
			isTexture = true;
		ImGui::SameLine();
		const char* listbox_items[] = { "1.jpg", "2.png", "3.jpg" };
		ImGui::ListBox("", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items), 3);
		{

		}
		ImGui::Text("------------------------------------------------");
		/*ImGui::Text("Wektor normalny z zaburzeniem");
		ImGui::Text("N'=N+D");*/
		ImGui::Text("N (wektor normalny przed zaburzeniem)");
		static int rb3 = 0;
		if (ImGui::RadioButton("Staly vector N [0,0,1]", &rb3, 0))
			isNormalMap = false;
		if (ImGui::RadioButton("Z tekstury \"Normal Map\" TODO", &rb3, 1))
			isNormalMap = true;
		ImGui::Text("------------------------------------------------");
		ImGui::Text("Zaburzenie D");
		static int rb4 = 0;
		ImGui::RadioButton("Brak [0,0,0]", &rb4, 0);
		ImGui::RadioButton("Z tekstury \"Height Map\" TODO", &rb4, 1);
	}

	/*{
		ImGui::SetNextWindowPos(ImVec2(0, 100));
		ImGui::SetNextWindowSize(ImVec2(300, 500));
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window2);
	}*/

	ImGui::Render();
}
void Manager::mouseCallback(int button, int state, int x, int y)
{
	if (getInstance()->mouseEvent(button, state, x, y))
	{
		glutPostRedisplay();
	}
}
void Manager::mouseDragCallback(int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	glutPostRedisplay();
}
void Manager::mouseMoveCallback(int x, int y)
{
	if ((x < WINDOW_WIDTH - MENU_WIDTH))
	{
		glutPassiveMotionFunc(mousePassiveFunc);
		return;
	}
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	glutPostRedisplay();
}
void Manager::keyboardCallback(unsigned char nChar, int x, int y)
{
	if (getInstance()->keyboardEvent(nChar, x, y))
	{
		glutPostRedisplay();
	}
}
bool Manager::mouseEvent(int button, int state, int x, int y)
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
bool Manager::keyboardEvent(unsigned char nChar, int nX, int nY)
{
	ImGuiIO& io = ImGui::GetIO();

	io.AddInputCharacter(nChar);

	return true;
}

