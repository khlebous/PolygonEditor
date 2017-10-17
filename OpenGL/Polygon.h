#pragma once
#include <vector>
#include <list>
#include <map>
#include "Edge.h"

using namespace std;

namespace GL
{
	class Polygon
	{
		vector<GL::Vertex> vertices;
		
		list<int> vEdges; // vertical Edges
		list<int> hEdges; // horizontal Edges
		vector<pair<int, float>> angles;

		bool isLooped = false;
		int maxDistToHighl = 5;

		//vector<GL::Edge> edges;
	public:
		Polygon();
		~Polygon();

		void AddVertex(int x, int y){ vertices.push_back(GL::Vertex(x, y)); }
		void AddVertex(GL::Point p){ vertices.push_back(GL::Vertex(p)); }

		vector<GL::Vertex> GetVertices(){ return vertices; }
		GL::Vertex GetVertex(int index){ return vertices[(index+vertices.size())%vertices.size()]; }
		int VertCount() { return vertices.size(); }
		list<int> GetVEdges() { return vEdges; }
		list<int> GetHEdges() { return hEdges; }
		vector<pair<int, float>> GetAngles() { return angles; }

		int CheckMouseNearVertice(int x, int y);
		int CheckMouseNearEdge(int x, int y);

		void MoveVertex(int vertNum, int x, int y);
		void AddVert(int n, int x, int y);
		void DeleteVert(int n);
		void MakeEdgeVertical(int n);
		void MakeEdgeHorizontal(int n);
		bool SetAngle(int n);

		void Loop();
		bool IsLooped() { return isLooped; }

		//void AddEdge(GL::Vertice v1, GL::Vertice v2){ edges.push_back(GL::Edge(v1, v2)); }
		//int EdgCount() { return edges.size(); }
		//GL::Edge GetEdge(int index){ return edges[index]; }

	private:
		bool CheckEdgeVetical(int n);
		bool CheckEdgeHorizontal(int n);
		bool CheckVertAngle(int n);
		//TODO how to name?
		void CheckEdgeVH(int n, list<int>* v1, list <int>* v2, bool checkV);

		void DeleteVertFromAngleVector(int n);
	};
}

