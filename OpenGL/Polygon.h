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
		vector<LineCoefficients> edgeCoeff;
		vector<pair<int, float>> vertSetAngle;
		//vector<SetAngle> setAngle;

		bool isLooped = false;
		int maxDistToHighl = 5;

	public:
		Polygon();
		~Polygon();

		void AddVertex(int x, int y){ AddVertex(GL::Point(x, y)); }
		void AddVertex(GL::Point p);

		vector<GL::Vertex> GetVertices(){ return vertices; }
		GL::Vertex GetVertex(int index){ return vertices[(index+vertices.size())%vertices.size()]; }
		int VertCount() { return vertices.size(); }
		list<int> GetVEdges() { return vEdges; }
		list<int> GetHEdges() { return hEdges; }
		vector<pair<int, float>>  GetAngles() { return vertSetAngle; }

		int CheckMouseNearVertice(int x, int y);
		int CheckMouseNearEdge(int x, int y);
		bool IsInside(int x, int y);
		void Loop();
		bool IsLooped() { return isLooped; }

		void MoveVertex(int vertNum, int x, int y);
		void AddVertAtEdge(int n, int x, int y);
		void DeleteVert(int n);

		void MakeEdgeVertical(int n);
		void MakeEdgeHorizontal(int n);

		bool SetAngleFunction(int n);

		void MovePolygon(int xOffset, int yOffset);

	private:
		bool CheckEdgeVetical(int n);
		bool CheckEdgeHorizontal(int n);
		//TODO how to name?
		bool CheckEdgeVH(int n, list<int>* v1, list <int>* v2, bool checkV);
		
		bool CheckAngleIsSetToVertex(int n);
		void UpdateAllEdgeCoeff();
		void UpdateEdgeCoeff(int n);
		//void DeleteVertFromAngleVector(int n);
		void DeleteSetAngle(int n);
		
		double Distance(double x1, double y1, double x2, double y2);
		GL::Vertex LineIntersection(GL::LineCoefficients lc1, GL::LineCoefficients lc2);
	};
}

