#pragma once
#include "Polygon.h"
#include <iostream>
#include <vector>
using namespace std;

namespace GL
{
	void FillPolygon(GL::Polygon* p);
	// L1
	void DrawPolygons(vector<GL::Polygon*> p, int highlightP, int highlightV, int highlightE,int choosedP1=-1, int choosedP2=-1);
	void DrawPolygon(GL::Polygon* p, bool choosed = false);

	void DrawVertice(GL::Vertex v, bool highlight=false);
	void DrawEdge(GL::Vertex v1, GL::Vertex v2, bool highlight=false);
	vector<pair<int,int>> CalculateLinePixels(GL::Vertex v1, GL::Vertex v2);

	void DrawVertSign(GL::Vertex v1, GL::Vertex v2);
	void DrawHorizSign(GL::Vertex v1, GL::Vertex v2);
	void DrawAngleSign(GL::Vertex v1);
}