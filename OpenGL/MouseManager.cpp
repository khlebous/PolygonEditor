#include "ExternVariables.h"
#include "MouseManager.h"

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
	// left click-> new vert & edge
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
		getInstance()->DrawNewVerticeAndEdge(x, y);
}
void MouseManager::mousePassiveFunc(int x, int y)
{
	MouseManager* instance = getInstance();
	if (!instance->CheckVertices(x, WINDOW_WIDTH - y))
		instance->CheckEdges(x, WINDOW_WIDTH - y);
	else if(instance->highlightEdge!=-1)
		instance->polygon->GetEdge(instance->highlightEdge);
}

void MouseManager::loopPolygon(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:  
		exit(0);
		break;
	case 'l':
		GL::Polygon* polygon = getInstance()->polygon;
		polygon->Loop();
		break;
	}
}

void MouseManager::DrawNewVerticeAndEdge(int x, int y)
{
	GL::Polygon* polygon = getInstance()->polygon;
	//TODO new function
	if (polygon->VertCount() > 2)
	{
		GL::Vertice v = polygon->GetVertice(0);
		if ((abs(v.GetX() - x) < 6) && (abs(v.GetY() - (WINDOW_WIDTH - y)) < 6))
			polygon->Loop();
	}
	//
	if (!polygon->IsLooped())
	{
		polygon->AddVertice(x, WINDOW_WIDTH - y);
		polygon->GetVertice(polygon->VertCount() - 1).Draw();

		if (polygon->VertCount() > 1)
		{
			polygon->AddEdge(polygon->GetVertice(polygon->VertCount() - 2),
				polygon->GetVertice(polygon->VertCount() - 1));
			polygon->GetEdge(polygon->VertCount() - 2).Draw();
		}
	}
}

bool MouseManager::CheckVertices(int x, int y)
{
	int v = polygon->CheckMouseNearVertice(x, y);
	if (v == -1)
	{
		if (highlightVertice != -1)
		{
			polygon->GetVertice(highlightVertice).UnhighlightVertice();
			highlightVertice = -1;
		}
		return false;
	}
	else if (highlightVertice != v)
	{
		if (highlightVertice != -1)
		{
			polygon->GetVertice(highlightVertice).UnhighlightVertice();
		}
		polygon->GetVertice(v).HighlightVertice();
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
			polygon->GetEdge(highlightEdge).Unhighlight();
			highlightEdge = -1;
		}
	}
	else if (highlightEdge != e)
	{
		if (highlightEdge != -1)
			polygon->GetEdge(highlightEdge).Unhighlight();
		polygon->GetEdge(e).Highlight();
		highlightEdge = e;
	}
}