#pragma once
#include <vector>
#include "Point.h"

using namespace std;

namespace GL
{
	class Polygon
	{
		vector<GL::Point> vertices;
		vector<vector<GL::Point>> edges;

	public:
		Polygon();
		~Polygon();

		void AddVertice(int x, int y);
		void AddVertice(GL::Point p);
		void AddEdge(vector < GL::Point> edge);
		GL::Point GetPoint(int index);
		int VerticesCount() { return vertices.size(); }
		GL::Point Check1(int x, int y);
	};
}

