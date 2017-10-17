#pragma once
#include "Polygon.h"
 
#include <vector>

using namespace std;

namespace GL
{
	void DrawPolygon(GL::Polygon* p, int highlightV=-1, int highlightE=-1);
	void DrawVertice(GL::Vertex v);
	void DrawHighlightVertice(GL::Vertex v);
	void DrawEdge(GL::Vertex v1, GL::Vertex v2);
	void DrawHighlightEdge(GL::Vertex v1, GL::Vertex v2);

	void DrawVertSign(GL::Vertex v1, GL::Vertex v2);
	void DrawHorizSign(GL::Vertex v1, GL::Vertex v2);
	void DrawAngleSign(GL::Vertex v1);

	void SetPixel(int x, int y, float size=1);
	/*void DrawVertice(int x, int y);
	void DrawHighlitVertice(int x, int y);
	vector<GL::Point> Line(int x1, int y1, int x2, int y2);
	void DrawEdge(GL::Polygon* polygon);
	void DrawEdge(vector<GL::Point> edge);
	void DrawHighlightEdge(vector<GL::Point> edge);

	void DrawEdge(GL::Vertice v1, GL::Vertice v2);
	void DrawEdge(GL::Point p1, GL::Point p2);*/
}
