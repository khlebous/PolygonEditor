#pragma once
#include "Polygon.h"
#include "Point.h"
#include <vector>

using namespace std;

namespace GL
{
	void SetPixel(int x, int y, float size=1);
	void DrawVertice(int x, int y);
	void DrawHighlitVertice(int x, int y);
	vector<GL::Point> Line(int x1, int y1, int x2, int y2);
	void Drawline(GL::Point p1, GL::Point p2);
	void DrawEdge(GL::Polygon* polygon);
}
