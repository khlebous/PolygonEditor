#pragma once
#include <vector>
#include <list>
#include "Edge.h"

using namespace std;

namespace GL
{
	class Polygon
	{
		vector<GL::Vertice> vertices;
		list<int> verticalEdges;
		//vector<GL::Edge> edges;

		bool isLooped = false;
		int maxDistToHighl = 5;
	public:
		Polygon();
		~Polygon();

		void AddVertice(int x, int y){ vertices.push_back(GL::Vertice(x, y)); }
		void AddVertice(GL::Point p){ vertices.push_back(GL::Vertice(p)); }
		//void AddEdge(GL::Vertice v1, GL::Vertice v2){ edges.push_back(GL::Edge(v1, v2)); }

		vector<GL::Vertice> GetVertices(){ return vertices; }
		GL::Vertice GetVertice(int index){ return vertices[index]; }
		int VertCount() { return vertices.size(); }
		//GL::Edge GetEdge(int index){ return edges[index]; }
		//int EdgCount() { return edges.size(); }

		int CheckMouseNearVertice(int x, int y);
		int CheckMouseNearEdge(int x, int y);

		void MoveVertice(int vertNum, int x, int y);
		void DeleteVert(int n);
		void MakeEdgeVertical(int n);

		void Loop();
		bool IsLooped() { return isLooped; }
	};
}

