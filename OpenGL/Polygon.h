#pragma once
#include <vector>
#include "Edge.h"

using namespace std;

namespace GL
{
	class Polygon
	{
		vector<GL::Vertice> vertices;
		vector<GL::Edge> edges;

		bool isLooped = false;
		int maxDistToHighl = 5;
	public:
		Polygon();
		~Polygon();

		void AddVertice(int x, int y);
		void AddVertice(GL::Point p);
		void AddEdge(GL::Vertice v1, GL::Vertice v2);

		GL::Vertice GetVertice(int index);
		GL::Edge GetEdge(int index);
		int VertCount() { return vertices.size(); }
		int EdgCount() { return edges.size(); }

		int CheckMouseNearVertice(int x, int y);
		int CheckMouseNearEdge(int x, int y);

		void Loop();
		bool IsLooped() { return isLooped; }
	};
}

