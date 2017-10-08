#pragma once
#include <vector>
#include "Point.h"
using namespace std;

namespace GL
{
	class Polygon
	{
		vector<GL::Point> vertices;

	public:
		Polygon();
		~Polygon();

		void AddVertice(int x, int y);
		void AddVertice(Point p);
		Point GetPoint(int index);
		int VerticesCount() { return vertices.size(); }
	};
}

