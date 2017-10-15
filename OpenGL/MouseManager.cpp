#include "ExternVariables.h"
#include "MouseManager.h"
#include "GraphicsLibrary.h"
//const int WINDOW_HEIGHT = 600;
//const int WINDOW_WIDTH = 300;

MouseManager* MouseManager::instance = NULL;

MouseManager::MouseManager()
{
	polygon = new GL::Polygon;
	highlightVertice = -1;
	highlightEdge = -1;
}
MouseManager* MouseManager::getInstance()
{
	if (!instance)
		instance = new MouseManager;
	return instance;
}
MouseManager::~MouseManager()
{
	polygon->~Polygon();
}

void MouseManager::mouseFunc(int button, int state, int x, int y)
{
	MouseManager* mm = getInstance();
	GL::Polygon* polygon = mm->polygon;
	// left click-> new vert & edge
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
	{
		glutIdleFunc(NULL);
	}
	else
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
		{
			if (polygon->IsLooped() && (mm->highlightVertice != -1))
			{
				glutIdleFunc(MouseManager::idleFunc);
				polygon->MoveVertice(mm->highlightVertice, x, WINDOW_WIDTH - y);

			}
			//TO y ->height-y
			//else
			//{
				//mm->isMoving = false;
			if (!polygon->IsLooped())
				mm->NewVerticeAndEdge(x, WINDOW_WIDTH - y);
			//}
		}
}
void MouseManager::mousePassiveFunc(int x, int y)
{
	MouseManager* mm = getInstance();
	/*if (mm->isMoving)
	{
		mm->polygon->MoveVertice(mm->highlightVertice, x, WINDOW_WIDTH - y);
		glutPostRedisplay();

	}
	else
	{*/
	if (!mm->CheckVertices(x, WINDOW_WIDTH - y))
		mm->CheckEdges(x, WINDOW_WIDTH - y);
	//else if (mm->highlightEdge != -1)
	//	mm->polygon->GetEdge(mm->highlightEdge);
	//}
}

void MouseManager::keyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27://esc
		exit(0);
		break;
	case 'a':
	{
		MouseManager* mm = getInstance();
		if (mm->highlightEdge != -1)
		{
			GL::Polygon* polygon = getInstance()->polygon;
			polygon->AddVert(mm->highlightEdge, x, WINDOW_WIDTH-y);
			//mm->highlightVertice = -1;
			GL::DrawPolygon(polygon);
		}
		break;
	}
	case 'd':
	{
		MouseManager* mm = getInstance();
		if (mm->highlightVertice != -1)
		{
			GL::Polygon* polygon = getInstance()->polygon;
			polygon->DeleteVert(mm->highlightVertice);
			mm->highlightVertice = -1;
			GL::DrawPolygon(polygon);
		}
		break;
	}
	case 'l': // loop polygon
	{
		GL::Polygon* polygon = getInstance()->polygon;
		polygon->Loop();
		GL::DrawPolygon(polygon);
		break;
	}
	case 'v':
	{
		MouseManager* mm = getInstance();
		if (mm->highlightEdge != -1)
		{
			GL::Polygon* polygon = getInstance()->polygon;
			polygon->MakeEdgeVertical(mm->highlightEdge);
			GL::DrawPolygon(getInstance()->polygon);
		}
		break;
	}
	case 'h':
	{
		MouseManager* mm = getInstance();
		if (mm->highlightEdge != -1)
		{
			GL::Polygon* polygon = getInstance()->polygon;
			polygon->MakeEdgeHorizontal(mm->highlightEdge);
			GL::DrawPolygon(getInstance()->polygon);
		}
		break;
	}
	}
}

void MouseManager::idleFunc()
{
	GL::DrawPolygon(getInstance()->polygon);
}

void MouseManager::motionFunc(int _x, int _y)
{
	MouseManager* mm = getInstance();
	if (mm->highlightVertice != -1)
		mm->polygon->MoveVertice(mm->highlightVertice, _x, WINDOW_WIDTH - _y);
	GL::DrawPolygon(mm->polygon);
}

void MouseManager::NewVerticeAndEdge(int x, int y)
{
	GL::Polygon* polygon = getInstance()->polygon;
	//TODO loop on click near vert0
	// jsesli kliknelismy w 0 i countV>=3
	/*if (polygon->VertCount() > 2)
	{
		GL::Vertice v = polygon->GetVertice(0);
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

	polygon->AddVertice(x, y);
	if (polygon->VertCount() > 1)
	{
		//		polygon->AddEdge(polygon->GetVertice(polygon->VertCount() - 2),
		//			polygon->GetVertice(polygon->VertCount() - 1));
	}
	GL::DrawPolygon(polygon);
}

bool MouseManager::CheckVertices(int x, int y)
{
	int v = polygon->CheckMouseNearVertice(x, y);
	if (v == -1)
	{
		if (highlightVertice != -1)
		{
			//polygon->GetVertice(highlightVertice).UnhighlightVertice();
			highlightVertice = -1;
		}
		return false;
	}
	else if (highlightVertice != v)
	{
		if (highlightVertice != -1)
		{
			//polygon->GetVertice(highlightVertice).UnhighlightVertice();
		}
		//polygon->GetVertice(v).HighlightVertice();
		highlightVertice = v;
	}
	return true;
}
void MouseManager::CheckEdges(int x, int y)
{
	int e = polygon->CheckMouseNearEdge(x, y);
	if (e == -1)
	{
		if (highlightEdge != -1)
		{
			//polygon->GetEdge(highlightEdge).Unhighlight();
			highlightEdge = -1;
		}
	}
	else if (highlightEdge != e)
	{
		//if (highlightEdge != -1)
			//polygon->GetEdge(highlightEdge).Unhighlight();
		//polygon->GetEdge(e).Highlight();
		highlightEdge = e;
	}
}