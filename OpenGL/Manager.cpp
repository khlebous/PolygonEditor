#include "ExternVariables.h"
#include "Manager.h"
#include "GraphicsLibrary.h"
#include <iostream>
using namespace std;
Manager* Manager::instance = NULL;

Manager::Manager()
{
	polygons = vector<GL::Polygon*>();
	GL::Polygon* pp = new GL::Polygon();
	pp->AddVertex(200, 150);
	pp->AddVertex(300, 200);
	pp->AddVertex(400, 50);
	pp->AddVertex(240,15);
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
		y = WINDOW_WIDTH - y;
		glutMotionFunc(Manager::motionFuncLeft);
		Manager* mm = getInstance();
		vector<GL::Polygon*> p = mm->polygons;

		//loop
		if (mm->highlightVertice == 0)
		{
			if (mm->polygons[mm->highlightPolygon]->Loop())
			{
				GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, -1);
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
		else if(mm->highlightVertice == -1)
			mm->NewVertexAndEdge(x, y);
		else
			mm->polygons[mm->highlightPolygon]->MoveVertex(mm->highlightVertice, x, y);
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
			GL::Polygon* polygon = mm->polygons[mm->highlightPolygon];
			polygon->AddVertAtEdge(mm->highlightEdge, x, WINDOW_WIDTH - y);
			GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
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
			GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
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
		GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
		break;
	}
	case 'v': // try to make edge vertical
	{
		Manager* mm = getInstance();
		if (mm->highlightEdge != -1)
		{
			GL::Polygon* p = mm->polygons[mm->highlightPolygon];
			p->MakeEdgeVertical(mm->highlightEdge);
			GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
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
			GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
		}
		break;
	}
	case 's': // set angle
	{
		Manager* mm = getInstance();
		if (mm->highlightVertice != -1)
			if (mm->polygons[mm->highlightPolygon]->SetAngleFunction(mm->highlightVertice))
				GL::DrawPolygons(mm->polygons, mm->highlightPolygon, mm->highlightVertice, mm->highlightEdge);
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
	if (mm->highlightVertice != -1)
	{
		/*if (mm->checkBox)
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
		}*/

		GL::Polygon* p = mm->polygons[mm->highlightPolygon];
		p->MoveVertex(mm->highlightVertice, _x, WINDOW_WIDTH - _y);
	}
	GL::DrawPolygons(mm->polygons, -1, -1, -1);
}

void Manager::motionFuncRight(int x, int y)
{
	y = WINDOW_WIDTH - y;
	Manager* mm = getInstance();
	mm->polygons[mm->_nr]->MovePolygon(x - mm->_x, y - mm->_y);
	mm->_x = x;
	mm->_y = y;
	GL::DrawPolygons(mm->polygons, -1, -1, -1);
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
			GL::DrawPolygons(polygons, -1, -1, -1);
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
		GL::DrawPolygons(polygons, highlightPolygon, highlightVertice, highlightEdge);
		return false;
	}
	if ((highlightVertice != v) || (highlightPolygon != p))
	{
		highlightVertice = v;
		highlightPolygon = p;
		GL::DrawPolygons(polygons, highlightPolygon, highlightVertice, highlightEdge);
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