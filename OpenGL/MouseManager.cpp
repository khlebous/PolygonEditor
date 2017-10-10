#include "ExternVariables.h"
#include "MouseManager.h"
#include "GraphicsLibrary.h"
#include <GL/glut.h> 
#include <stdlib.h> 

MouseManager* MouseManager::instance = NULL;

MouseManager::MouseManager()
{
	polygon = new GL::Polygon;
	highlightVertice = GL::Point(-1, -1);
	highlightEdge = vector<GL::Point>();
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
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		getInstance()->DrawNewVerticeAndEdge(x, y);
	}

}

void MouseManager::mouse2(int x, int y)
{
	getInstance()->CheckVertices(x, WINDOW_WIDTH - y);
	getInstance()->CheckEdges(x, WINDOW_WIDTH - y);
	//GL::SetPixel(x, WINDOW_WIDTH- y);
}

void MouseManager::DrawNewVerticeAndEdge(int x, int y)
{
	GL::Polygon* polygon = getInstance()->polygon;
	polygon->AddVertice(x, WINDOW_WIDTH - y);

	GL::DrawVertice(x, WINDOW_WIDTH - y);
	if (polygon->VerticesCount() > 1)
		GL::DrawEdge(polygon);

}

bool MouseManager::CheckVertices(int x, int y)
{
	GL::Point p = polygon->CheckMouseNearVertice(x, y);
	// TODO find bug
	if (p.x == -1)
	{
		if (highlightVertice.x != -1)
		{
			GL::DrawVertice(highlightVertice.x, highlightVertice.y);
			highlightVertice = GL::Point(-1, -1);
		}
	}
	else
	{
		/*if (highlightVertice.x == -1)
		{
			highlightVertice = p;
			GL::DrawHighlitVertice(p.x, p.y);
		}
		else */if(highlightVertice!=p)
		{
			if (highlightVertice.x != -1)
				GL::DrawVertice(highlightVertice.x, highlightVertice.y);
			GL::DrawHighlitVertice(p.x, p.y);
			highlightVertice = p;
		}
	}
	return true;
}

bool MouseManager::CheckEdges(int x, int y)
{
	vector<GL::Point> e = polygon->CheckMouseNearEdge(x, y);
	// TODO find bug
	if (e.size()==0)
	{
		if (highlightEdge.size() == 0)
		{
			GL::DrawEdge(highlightEdge);
			highlightEdge = vector<GL::Point>();
		}
	}
	else
	{
		/*if (highlightVertice.x == -1)
		{
		highlightVertice = p;
		GL::DrawHighlitVertice(p.x, p.y);
		}
		else */
		if (highlightEdge != e)
		{
			if (highlightEdge.size()>0)
				GL::DrawEdge(highlightEdge);
			GL::DrawHighlightEdge(e);
			highlightEdge = e;
		}
	}
	return true;
}
