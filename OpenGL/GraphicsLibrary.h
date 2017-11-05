#pragma once
#include "Polygon.h"
#include <iostream>
#include <vector>
using namespace std;

namespace GL
{
	void FillPolygon(GL::Polygon* p);
	// L1
	void DrawPolygons(vector<GL::Polygon*> p, int highlightP, int highlightV, int highlightE);
	void DrawPolygon(GL::Polygon* p);

	void DrawVertice(GL::Vertex v);
	void DrawHighlightVertice(GL::Vertex v);
	
	void DrawEdge(GL::Vertex v1, GL::Vertex v2);
	void DrawHighlightEdge(GL::Vertex v1, GL::Vertex v2);
	vector<GL::Point> CalculateLinePixels(GL::Vertex v1, GL::Vertex v2);

	void DrawVertSign(GL::Vertex v1, GL::Vertex v2);
	void DrawHorizSign(GL::Vertex v1, GL::Vertex v2);
	void DrawAngleSign(GL::Vertex v1);
}