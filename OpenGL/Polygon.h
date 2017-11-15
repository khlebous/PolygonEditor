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
		int isLooped;
	public:
		Polygon();
		~Polygon();

		list<int> vTmpEdges; // vertical temporary Edges
		list<int> hTmpEdges; // horizontal temporary Edges

		void AddVertex(int x, int y){ AddVertex(GL::Vertex(x, y)); }
		void AddVertex(GL::Vertex p);

		vector<GL::Vertex> GetVertices(){ return vertices; }
		GL::Vertex GetVertex(int index){ return vertices[(index+vertices.size())%vertices.size()]; }
		int VertCount() { return vertices.size(); }
		list<int> GetVEdges() { return vEdges; }
		list<int> GetHEdges() { return hEdges; }
		list<int> GetVEdgesTmp() { return vTmpEdges; }
		list<int> GetHEdgesTmp() { return hTmpEdges; }
		vector<pair<int, float>>  GetAngles() { return vertSetAngle; }

		int CheckMouseNearVertice(int x, int y);
		int CheckMouseNearEdge(int x, int y);
		bool IsInside(int x, int y);
		bool Loop();
		bool IsLooped() { return isLooped==1; }

		void MoveVertex(int vertNum, int x, int y);
		void AddVertAtEdge(int n, int x, int y);
		void DeleteVert(int n);

		void MakeEdgeVertical(int n);
		void MakeEdgeHorizontal(int n);
		bool EdgeNearVertical(int n);
		bool EdgeNearHorizontal(int n);

		bool SetAngleFunction(int n);

		void MovePolygon(int xOffset, int yOffset);
		bool CheckConvex();
	private:
		bool CheckEdgeVetical(int n);
		bool CheckEdgeHorizontal(int n);
		void CheckEdgeVH(int n, list<int>* v1, list <int>* v2, bool checkV);
		
		bool CheckAngleIsSetToVertex(int n);
		void UpdateAllEdgeCoeff();
		void UpdateEdgeCoeff(int n);
		void DeleteSetAngle(int n);
		
		double Distance(double x1, double y1, double x2, double y2);
		GL::Vertex LineIntersection(GL::LineCoefficients lc1, GL::LineCoefficients lc2);
	};
}

