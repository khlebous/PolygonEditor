#include "ExternVariables.h"
#include "Manager.h"
#include "GraphicsLibrary.h"
#include <iostream>
using namespace std;
Manager* Manager::instance = NULL;

Manager::Manager()
{
	polygon = new GL::Polygon;
	polygon2 = new GL::Polygon;
	highlightVertice = -1;
	highlightEdge = -1;
	_x = -1;
	_y = -1;
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
		glutMotionFunc(NULL);
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		glutMotionFunc(Manager::motionFuncLeft);
		Manager* mm = getInstance();
		GL::Polygon* polygon = mm->polygon;
		GL::Polygon* polygon2 = mm->polygon2;
		if (polygon->IsLooped() && (mm->highlightVertice != -1))
			polygon->MoveVertex(mm->highlightVertice, x, WINDOW_WIDTH - y);
		else if (polygon->IsLooped() && polygon->IsInside(x, WINDOW_WIDTH - y))
		{
			glutMotionFunc(Manager::motionFuncRight);
			mm->_x = x;
			mm->_y = WINDOW_WIDTH - y;
		}
		else if (!polygon->IsLooped())
			mm->NewVerticeAndEdge(polygon, x, WINDOW_WIDTH - y);
		else if (!polygon2->IsLooped())
			mm->NewVerticeAndEdge(polygon2, x, WINDOW_WIDTH - y);
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
			polygon->AddVertAtEdge(mm->highlightEdge, x, WINDOW_WIDTH - y);
			GL::DrawPolygon(polygon, getInstance()->polygon2, mm->highlightVertice, mm->highlightEdge);
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
			GL::DrawPolygon(polygon, getInstance()->polygon2, mm->highlightVertice, mm->highlightEdge);
		}
		break;
	}
	case 'l': // loop polygon
	{
		Manager* mm = getInstance();
		GL::Polygon* polygon = mm->polygon;
		GL::Polygon* polygon2 = mm->polygon2;
		if (!polygon->IsLooped())
		{
			polygon->Loop();
		}
		else if (!polygon2->IsLooped())
		{
			mm->polygon2->Loop();
		}
		GL::DrawPolygon(polygon, getInstance()->polygon2, mm->highlightVertice, mm->highlightEdge);

		break;
	}
	case 'v': // try to make edge vertical
	{
		Manager* mm = getInstance();
		if (mm->highlightEdge != -1)
		{
			GL::Polygon* polygon = getInstance()->polygon;
			polygon->MakeEdgeVertical(mm->highlightEdge);
			GL::DrawPolygon(polygon, mm->polygon2, mm->highlightVertice, mm->highlightEdge);

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
			GL::DrawPolygon(polygon, mm->polygon2, mm->highlightVertice, mm->highlightEdge);
		}
		break;
	}
	case 's': // set angle
	{
		Manager* mm = getInstance();
		if (mm->highlightVertice != -1)
			if (mm->polygon->SetAngleFunction(mm->highlightVertice))
				GL::DrawPolygon(mm->polygon, mm->polygon2, mm->highlightVertice, mm->highlightEdge);
		break;
	}
	case 'c': // checkbox
	{
		Manager* mm = getInstance();
		mm->checkBox = !mm->checkBox;
		if (mm->checkBox)
			cout << "checkbox on\n";
		else
			cout << "checkbox off\n";
	}
	}
}

void Manager::motionFuncLeft(int _x, int _y)
{
	Manager* mm = getInstance();
	GL::Polygon* p = mm->polygon;
	if (mm->highlightVertice != -1)
	{
		if (mm->checkBox)
		{
			if (p->EdgeNearVertical(mm->highlightVertice))
			{
				auto it = find(p->vTmpEdges.begin(), p->vTmpEdges.end(), mm->highlightVertice);
				if (it == p->vTmpEdges.end())
					p->vTmpEdges.push_back(mm->highlightVertice);
			}
			else
				p->vTmpEdges = list<int>();
			if (p->EdgeNearHorizontal(mm->highlightVertice))
			{
				auto it = find(p->hTmpEdges.begin(), p->hTmpEdges.end(), mm->highlightVertice);
				if (it == p->hTmpEdges.end())
					p->hTmpEdges.push_back(mm->highlightVertice);
			}
			else
				p->hTmpEdges = list<int>();
			int n1 = (mm->highlightVertice - 1) % (p->VertCount());
			if (p->EdgeNearVertical(n1))
			{
				auto it = find(p->vTmpEdges.begin(), p->vTmpEdges.end(), n1);
				if (it == p->vTmpEdges.end())
					p->vTmpEdges.push_back(n1);
			}
			else
				p->vTmpEdges = list<int>();
			if (p->EdgeNearHorizontal(n1))
			{
				auto it = find(p->hTmpEdges.begin(), p->hTmpEdges.end(), n1);
				if (it == p->hTmpEdges.end())
					p->hTmpEdges.push_back(n1);
			}
			else
				p->hTmpEdges = list<int>();
		}


		p->MoveVertex(mm->highlightVertice, _x, WINDOW_WIDTH - _y);
	}
	GL::DrawPolygon(mm->polygon, mm->polygon2);
}

void Manager::motionFuncRight(int x, int y)
{
	Manager* mm = getInstance();
	mm->polygon->MovePolygon(x - mm->_x, WINDOW_WIDTH - y - mm->_y);
	mm->_x = x;
	mm->_y = WINDOW_WIDTH - y;
	GL::DrawPolygon(mm->polygon, mm->polygon2);
}

//=====================================================
//private
void Manager::NewVerticeAndEdge(GL::Polygon *polygon, int x, int y)
{
	//GL::Polygon* polygon = getInstance()->polygon;
	if (polygon->VertCount() > 0)
		if ((highlightVertice==0) && (!polygon->IsLooped()))
		{
			polygon->Loop();
			GL::DrawPolygon(getInstance()->polygon, getInstance()->polygon2);
			return;
		}

	if (polygon->CheckMouseNearVertice(x, y) != -1)
	{
		return;
	}
	polygon->AddVertex(x, y);
	if (polygon->VertCount() > 1)
		GL::DrawPolygon(getInstance()->polygon, getInstance()->polygon2);
}

bool Manager::CheckVertices(int x, int y)
{
	int v = polygon->CheckMouseNearVertice(x, y);
	if (v == -1)
	{
		if (highlightVertice != -1)
		{
			highlightVertice = -1;
			GL::DrawPolygon(polygon, getInstance()->polygon2, highlightVertice, highlightEdge);
		}
		return false;
	}
	else if (highlightVertice != v)
	{
		highlightVertice = v;
		GL::DrawPolygon(polygon, getInstance()->polygon2, highlightVertice, highlightEdge);
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
			highlightEdge = -1;
			GL::DrawPolygon(polygon, getInstance()->polygon2, highlightVertice, highlightEdge);
		}
	}
	else if (highlightEdge != e)
	{
		highlightEdge = e;
		GL::DrawPolygon(polygon, getInstance()->polygon2, highlightVertice, highlightEdge);
	}
}