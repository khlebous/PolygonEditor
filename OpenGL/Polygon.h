#pragma once
#include <vector>
#include <list>
#include <map>
#include "Edge.h"
#include "SetAngle.h"

using namespace std;

namespace GL
{
	class Polygon
	{
		vector<GL::Vertex> vertices;
		list<int> vEdges; // vertical Edges
		list<int> hEdges; // horizontal Edges
		vector<SetAngle> setAngle;

		bool isLooped = false;
		int maxDistToHighl = 5;

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
		vector<SetAngle>  GetAngles() { return setAngle; }

		int CheckMouseNearVertice(int x, int y);
		int CheckMouseNearEdge(int x, int y);

		void MoveVertex(int vertNum, int x, int y);
		void MovePolygon(int xOffset, int yOffset);
		void AddVert(int n, int x, int y);
		void DeleteVert(int n);
		void MakeEdgeVertical(int n);
		void MakeEdgeHorizontal(int n);
		bool SetAngleFunction(int n);

		bool IsInside(int x, int y);
		void Loop();
		bool IsLooped() { return isLooped; }

	private:
		bool CheckEdgeVetical(int n);
		bool CheckEdgeHorizontal(int n);
		bool CheckAngleIsSetToVertex(int n);
		void UpdateLineParametries();
		//TODO how to name?
		void CheckEdgeVH(int n, list<int>* v1, list <int>* v2, bool checkV);

		//void DeleteVertFromAngleVector(int n);
		void DeleteSetAngle(int n);
		GL::Vertex LineIntersection(GL::LineCoefficients lc1, GL::LineCoefficients lc2);
	};
}

