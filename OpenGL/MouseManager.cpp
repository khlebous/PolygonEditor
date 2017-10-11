#include "ExternVariables.h"
#include "MouseManager.h"

MouseManager* MouseManager::instance = NULL;

MouseManager::MouseManager()
{
	polygon = new GL::Polygon;
	highlightVertice = GL::Vertice(-1, -1);
	highlightEdge = GL::Edge();
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
	else
		instance->UnhighlightEdge();
}

void MouseManager::UnhighlightVertice()
{
	highlightVertice.UnhighlightVertice();
	highlightVertice = GL::Vertice(-1, -1);
}

void MouseManager::UnhighlightEdge()
{
	highlightEdge.Unhighlight();
	highlightEdge = GL::Edge();
}

void MouseManager::DrawNewVerticeAndEdge(int x, int y)
{
	GL::Polygon* polygon = getInstance()->polygon;

	//TODO new function
	if (polygon->VertCount() > 2)
	{
		GL::Vertice v = polygon->GetVertice(0);
		if ((abs(v.GetX() - x) < 6) && (abs(v.GetY() - (WINDOW_WIDTH-y)) < 6))
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
	GL::Vertice v = polygon->CheckMouseNearVertice(x, y);
	if (v.GetX() == -1)
	{
		if (highlightVertice.GetX() != -1)
		{
			highlightVertice.UnhighlightVertice();
			highlightVertice = GL::Vertice(-1, -1);
		}
		return false;
	}
	else if (highlightVertice != v)
	{
		if (highlightVertice.GetX() != -1)
			highlightVertice.UnhighlightVertice();
		v.HighlightVertice();
		highlightVertice = v;
	}
	return true;
}
void MouseManager::CheckEdges(int x, int y)
{
	GL::Edge e = polygon->CheckMouseNearEdge(x, y);
	if (e.Length() == 0)
	{
		if (highlightEdge.Length() != 0)
		{
			highlightEdge.Unhighlight();
			highlightEdge = GL::Edge();
		}
	}
	else if (highlightEdge != e)
	{
		if (highlightEdge.Length() > 0)
			highlightEdge.Unhighlight();
		e.Highlight();
		highlightEdge = e;
	}
}