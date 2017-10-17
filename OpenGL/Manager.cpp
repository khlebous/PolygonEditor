#include "ExternVariables.h"
#include "Manager.h"
#include "GraphicsLibrary.h"
#include <iostream>
//const int WINDOW_HEIGHT = 600;
//const int WINDOW_WIDTH = 300;
using namespace std;
Manager* Manager::instance = NULL;

Manager::Manager()
{
	polygon = new GL::Polygon;
	highlightVertice = -1;
	highlightEdge = -1;
}
Manager* Manager::getInstance()
{
	if (!instance)
		instance = new Manager;
	return instance;
}
Manager::~Manager()
{
	polygon->~Polygon();
}

void Manager::mouseFunc(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
	{
		glutIdleFunc(NULL);
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		Manager* mm = getInstance();
		GL::Polygon* polygon = mm->polygon;
		if (polygon->IsLooped() && (mm->highlightVertice != -1))
		{
			glutIdleFunc(Manager::idleFunc);
			polygon->MoveVertex(mm->highlightVertice, x, WINDOW_WIDTH - y);
		}
		if (!polygon->IsLooped())
			mm->NewVerticeAndEdge(x, WINDOW_WIDTH - y);
	}
}
void Manager::mousePassiveFunc(int x, int y)
{
	Manager* mm = getInstance();
	if (!mm->CheckVertices(x, WINDOW_WIDTH - y))
		mm->CheckEdges(x, WINDOW_WIDTH - y);
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
			GL::Polygon* polygon = getInstance()->polygon;
			polygon->AddVert(mm->highlightEdge, x, WINDOW_WIDTH - y);
			GL::DrawPolygon(polygon, mm->highlightVertice, mm->highlightEdge);
		}
		break;
	}
	case 'd': //delete vertex
	{
		Manager* mm = getInstance();
		if (mm->highlightVertice != -1)
		{
			GL::Polygon* polygon = getInstance()->polygon;
			polygon->DeleteVert(mm->highlightVertice);
			mm->highlightVertice = -1;
			GL::DrawPolygon(polygon, mm->highlightVertice, mm->highlightEdge);

		}
		break;
	}
	case 'l': // loop polygon
	{
		Manager* mm = getInstance();
		GL::Polygon* polygon = mm->polygon;
		polygon->Loop();
		GL::DrawPolygon(polygon, mm->highlightVertice, mm->highlightEdge);

		break;
	}
	case 'v': // try to make edge vertical
	{
		Manager* mm = getInstance();
		if (mm->highlightEdge != -1)
		{
			GL::Polygon* polygon = getInstance()->polygon;
			polygon->MakeEdgeVertical(mm->highlightEdge);
			GL::DrawPolygon(polygon, mm->highlightVertice, mm->highlightEdge);

		}
		break;
	}
	case 'h': // try to make edge horizontal
	{
		Manager* mm = getInstance();
		if (mm->highlightEdge != -1)
		{
			GL::Polygon* polygon = getInstance()->polygon;
			polygon->MakeEdgeHorizontal(mm->highlightEdge);
			GL::DrawPolygon(polygon, mm->highlightVertice, mm->highlightEdge);
		}
		break;
	}
	case 's': // set angle
	{
		Manager* mm = getInstance();
		if (mm->highlightVertice != -1)
			if (mm->polygon->SetAngle(mm->highlightVertice))
			{
				GL::DrawPolygon(mm->polygon, mm->highlightVertice, mm->highlightEdge);
				cout << "new draw\n";
			}
			else
				cout << "can't set angle!!\n";
		break;
	}
	}
}

void Manager::idleFunc()
{
	Manager* mm = getInstance();
	GL::DrawPolygon(mm->polygon, mm->highlightVertice, mm->highlightEdge);
}

void Manager::motionFunc(int _x, int _y)
{
	Manager* mm = getInstance();
	if (mm->highlightVertice != -1)
		mm->polygon->MoveVertex(mm->highlightVertice, _x, WINDOW_WIDTH - _y);
	GL::DrawPolygon(mm->polygon);
}

void Manager::NewVerticeAndEdge(int x, int y)
{
	GL::Polygon* polygon = getInstance()->polygon;
	//TODO loop on click near vert0
	// jsesli kliknelismy w 0 i countV>=3
	/*if (polygon->VertCount() > 2)
	{
		GL::Vertice v = polygon->GetVertex(0);
		if ((abs(v.GetX() - x) < 6) && (abs(v.GetY() - (WINDOW_WIDTH - y)) < 6))
		{
			polygon->Loop();
			GL::DrawPolygon(polygon);
			return;
		}
	}*/
	//
	if (polygon->CheckMouseNearVertice(x, y) != -1)
		return;

	polygon->AddVertex(x, y);
	if (polygon->VertCount() > 1)
	{
		//		polygon->AddEdge(polygon->GetVertex(polygon->VertCount() - 2),
		//			polygon->GetVertex(polygon->VertCount() - 1));
	}
	GL::DrawPolygon(polygon);
}

bool Manager::CheckVertices(int x, int y)
{
	int v = polygon->CheckMouseNearVertice(x, y);
	if (v == -1)
	{
		if (highlightVertice != -1)
		{
			//polygon->GetVertex(highlightVertice).UnhighlightVertex();
			highlightVertice = -1;
			GL::DrawPolygon(polygon, highlightVertice, highlightEdge);
		}
		return false;
	}
	else if (highlightVertice != v)
	{
		if (highlightVertice != -1)
		{
			//polygon->GetVertex(highlightVertice).UnhighlightVertex();
		}
		//polygon->GetVertex(v).HighlightVertex();
		highlightVertice = v;
		GL::DrawPolygon(polygon, highlightVertice, highlightEdge);
	}
	return true;
}
void Manager::CheckEdges(int x, int y)
{
	int e = polygon->CheckMouseNearEdge(x, y);
	if (e == -1)
	{
		if (highlightEdge != -1)
		{
			//polygon->GetEdge(highlightEdge).Unhighlight();
			highlightEdge = -1;
			GL::DrawPolygon(polygon, highlightVertice, highlightEdge);


		}
	}
	else if (highlightEdge != e)
	{
		//if (highlightEdge != -1)
			//polygon->GetEdge(highlightEdge).Unhighlight();
		//polygon->GetEdge(e).Highlight();
		highlightEdge = e;
		GL::DrawPolygon(polygon, highlightVertice, highlightEdge);

	}
}