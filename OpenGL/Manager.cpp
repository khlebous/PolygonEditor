#include "GL/glew.h"
#include "GL/freeglut.h"

#include "imgui\imgui.h"
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
	GL::Polygon* p1 = new GL::Polygon();
	p1->AddVertex(400, 40);
	p1->AddVertex(800, 40);
	p1->AddVertex(800, 500);
	p1->AddVertex(500, 200);
	p1->AddVertex(400, 400);
	p1->Loop();
	GL::Polygon* p2 = new GL::Polygon();
	p2->AddVertex(40, 50);
	p2->AddVertex(350, 50);
	p2->AddVertex(300, 500);
	p2->AddVertex(50, 500);
	p2->Loop();
	polygons.push_back(p2);
	polygons.push_back(p1);
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
				if (mm->choosedPolygon1 == -1)
				{
					mm->choosedPolygon1 =i;
				}
				else if (mm->choosedPolygon2 == -1)
					mm->choosedPolygon2 = mm->_nr;
				else if(mm->choosedPolygon2 != i)
				{
					mm->choosedPolygon1 = mm->choosedPolygon2;
					mm->choosedPolygon2 = i;
				}
				break;
			}
			mm->_nr = -1;
		}
		if ((-1 != mm->_nr))
		{
			
			if (mm->highlightPolygon == -1)
			{
				glutMotionFunc(Manager::motionFuncRight);
				mm->_x = x;
				mm->_y = y;
			}
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
			drawScene();
		}
		break;
	}
	case 'l': // loop polygon
	{
		Manager* mm = getInstance();
		GL::Polygon* p = mm->polygons[mm->polygons.size() - 1];
		if (!p->IsLooped())
			p->Loop();
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
	drawScene();
}
void Manager::motionFuncRight(int x, int y)
{
	y = WINDOW_HEIGHT - y;
	Manager* mm = getInstance();
	mm->polygons[mm->_nr]->MovePolygon(x - mm->_x, y - mm->_y);
	mm->_x = x;
	mm->_y = y;
	glutPostRedisplay();
}
void Manager::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// add code here to draw scene objects

	// draw gui
	Manager* mm = getInstance();
	GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge, mm->choosedPolygon1, mm->choosedPolygon2);
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
		if (!(p->IsLooped()))
		{
			p->AddVertex(x, y);
			glutPostRedisplay();
			return;
		}
	}
	GL::Polygon* pp = new GL::Polygon();
	polygons.push_back(pp);
	polygons[polygons.size() - 1]->AddVertex(x, y);
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
		glutPostRedisplay();
		return false;
	}
	if ((highlightVertice != v) || (highlightPolygon != p))
	{
		highlightVertice = v;
		glutPostRedisplay();
		highlightPolygon = p;
	}
	glutPostRedisplay();
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
			glutPostRedisplay();
		}
	}
	else if ((highlightEdge != e) || (highlightPolygon != p))
	{
		highlightEdge = e;
		highlightPolygon = p;
		glutPostRedisplay();
	}
}

void Manager::ClippingPolygons()
{
	if (choosedPolygon1 == -1 || choosedPolygon2 == -1)
		return;
	if (polygons[choosedPolygon1]->CheckConvex())
	{
		SutherlandHodgman(choosedPolygon1, choosedPolygon2);
		polygons.erase(polygons.begin() + choosedPolygon1);
	}
	else if (polygons[choosedPolygon2]->CheckConvex())
	{
		SutherlandHodgman(choosedPolygon2, choosedPolygon1);
		polygons.erase(polygons.begin() + choosedPolygon2);
	}
	choosedPolygon1 = -1;
	choosedPolygon2 = -1;
	glutPostRedisplay();
}
bool IsSameSide(GL::Vertex p1, GL::Vertex insidePoint, GL::Vertex p0, GL::Vertex p2)
{
	bool isSameSide = false; // 
	double tmp1 = (p1.GetX() - p0.GetX()) * (p2.GetY() - p0.GetY()) - (p2.GetX() - p0.GetX()) * (p1.GetY() - p0.GetY());
	double tmp2 = (insidePoint.GetX() - p0.GetX()) * (p2.GetY() - p0.GetY()) - (p2.GetX() - p0.GetX()) * (insidePoint.GetY() - p0.GetY());
	if (tmp1 * tmp2 >= 0)
		isSameSide = true;
	return isSameSide;
}
void Manager::SutherlandHodgman(int clipPolygonNr, int subjectPolygonNr)
{
	vector<GL::Vertex> przeciecie = vector<GL::Vertex>();
	vector<GL::Vertex> output = vector<GL::Vertex>();
	output = polygons[subjectPolygonNr]->GetVertices();
	vector<GL::Vertex>clipPolygon = polygons[clipPolygonNr]->GetVertices();
	vector<GL::Vertex>subjectPolygon = polygons[subjectPolygonNr]->GetVertices();
	int n = polygons[clipPolygonNr]->VertCount();

	GL::Vertex insidePoint = GL::Vertex((clipPolygon[0].GetX() + clipPolygon[1].GetX() + clipPolygon[2].GetX()) / 3,
		(clipPolygon[0].GetY() + clipPolygon[1].GetY() + clipPolygon[2].GetY()) / 3);
	for (int i = 0; i < n; i++)
	{
		// e - pocz - clipPolig[i]
		//     koniec [i+1]
		vector<GL::Vertex> input = output;
		if (input.size() == 0)
			break;
		output = vector<GL::Vertex>();
		GL::Vertex pp = input[input.size() - 1];
		for (GL::Vertex &p : input)
		{
			GL::Vertex p1 = p;
			GL::Vertex p0 = clipPolygon[i];
			GL::Vertex p2 = GL::Vertex();
			if (i + 1 == clipPolygon.size())
				p2 = clipPolygon[0];
			else
				p2 = clipPolygon[i + 1];

			bool isSameSide = IsSameSide(p1, insidePoint, p0, p2);
			if (isSameSide) // p po wewn stronie
			{
				p1 = pp;
				isSameSide = IsSameSide(p1, insidePoint, p0, p2);
				if (!isSameSide) // pp nie po wewn
				{
					GL::LineCoefficients lc1 = GL::LineCoefficients(pp, p);
					GL::LineCoefficients lc2 = GL::LineCoefficients(p0, p2);
					output.push_back(lc1.LineIntersection(lc2));
				}
				if (output.size() == 0)
					output.push_back(p);
				else if (output[output.size() - 1] != p)
					output.push_back(p);
			}
			else
			{
				p1 = pp;
				isSameSide = IsSameSide(p1, insidePoint, p0, p2);
				if (isSameSide) // pp po wewn
				{
					GL::LineCoefficients lc1 = GL::LineCoefficients(pp, p);
					GL::LineCoefficients lc2 = GL::LineCoefficients(p0, p2);
					GL::Vertex tmp = lc1.LineIntersection(lc2);
					if (output.size() == 0)
						output.push_back(tmp);
					else if (output[output.size() - 1] != tmp)
						output.push_back(tmp);
				}
			}
			pp = p;
		}
	}
	if (output.size() > 0 && output[0] == output[output.size() - 1])
		output.erase(output.begin() + output.size() - 1);
	if (output.size() == 0)
	{
		polygons[subjectPolygonNr]= new GL::Polygon();
	}
	else
		polygons[subjectPolygonNr]->SetVertices(output);
}

void Manager::drawGUI()
{
	ImGui_ImplGLUT_NewFrame(WINDOW_WIDTH, WINDOW_HEIGHT);
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
		if (ImGui::CollapsingHeader("Klawiszologia"))
		{
			ImGui::TextWrapped("Zeby zrobic obcinanie trzeba spoczatku wybrac dwa wilokaty (Jesli wielokat jest wybrany ma wszystkie krawedzie i wierzcholki na czerwono). Nastepnie trzeba wcinac przycisk \"obcinanie\"\n\n");
			ImGui::TextWrapped("Wszystkie kolory mozna zmienic wpisujac liczby zamiast R, G lub B w odpowiednie miejsca albo wciskajac kwadrat po prawej od tych liczb i wybierajac kolor\n\n");
			ImGui::TextWrapped("Radius i wysokosc swiatla animowanego zmienia sie za pomoca suwakow\n\n");
			ImGui::TextWrapped("Teksuty/mapy normalny mozna zmieniac wybierajac z podanych list tekstur/map normalnych");
		}
		ImGui::Text("------------------------------------------------");
		if (ImGui::Button("Obcinanie (Sutherland Hodgman)"))
			ClippingPolygons();
		ImGui::Text("------------------------------------------------");
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
		if (ImGui::RadioButton("Staly [0,0,1]", &rb1, 0))
		{
			isLightAnimated = false;
			glutPostRedisplay();
		}
		if (ImGui::RadioButton("Swiatlo animowane", &rb1, 1))
		{
			isLightAnimated = true;
			glutPostRedisplay();
		}
		ImGui::SliderInt("Radius", &lightRadius, 1, 500);
		ImGui::SliderInt("Wysokosc", &lightPositionZ, 50, 200);
		ImGui::Text("------------------------------------------------");
		ImGui::Text("Kolor obiektu");
		static int rb2 = 0;
		if (ImGui::RadioButton("Z tekstury", &rb2, 0))
		{
			isTexture = true;
			glutPostRedisplay();
		}
		//ImGui::SameLine();
		const char* listbox_items[] = { "human", "banana", "bricks" };
		ImGui::ListBox(" ", &textureNr, listbox_items, IM_ARRAYSIZE(listbox_items), 3);
		if (lastTexture != textureNr)
		{
			lastTexture = textureNr;
			glutPostRedisplay();
		}
		if (ImGui::RadioButton("Staly kolor", &rb2, 1))
		{
			isTexture = false;
			glutPostRedisplay();
		}
		ImGui::SameLine();
		if (ImGui::ColorEdit3("##1", (float*)&fillColor, misc_flags))
		{
			polygonFillColorR = fillColor.x;
			polygonFillColorG = fillColor.y;
			polygonFillColorB = fillColor.z;
		}
		ImGui::Text("------------------------------------------------");
		/*ImGui::Text("Wektor normalny z zaburzeniem");
		ImGui::Text("N'=N+D");*/
		ImGui::Text("N (wektor normalny przed zaburzeniem)");
		static int rb3 = 0;
		if (ImGui::RadioButton("Z tekstury \"Normal Map\" TODO list", &rb3, 0))
		{
			isNormalMap = true;
			glutPostRedisplay();
		}
		const char* listbox_items2[] = { "human", "hemisphere", "hemisphereAndOther", "bricks" };
		ImGui::ListBox("qwe", &normalMapNr, listbox_items2, IM_ARRAYSIZE(listbox_items2), 4);
		if (lastNormalMap != normalMapNr)
		{
			lastNormalMap = normalMapNr;
			glutPostRedisplay();
		}
		if (ImGui::RadioButton("Staly vector N [0,0,1]", &rb3, 1))
		{
			isNormalMap = false;
			glutPostRedisplay();
		}
		ImGui::Text("------------------------------------------------");
		ImGui::Text("Zaburzenie D");
		static int rb4 = 0;
		ImGui::RadioButton("Brak [0,0,0]", &rb4, 0);
		ImGui::RadioButton("Z tekstury \"Height Map\" TODO", &rb4, 1);
		
	}
	ImGui::Render();
}
void Manager::mouseCallback(int button, int state, int x, int y)
{
	if (getInstance()->mouseEvent(button, state, x, y))
		glutPostRedisplay();
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
		glutPostRedisplay();
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

