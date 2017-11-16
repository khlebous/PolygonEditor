#pragma once
#include <vector>
#include <list>
#include <map>
#include "SetAngle.h"

using namespace std;

namespace GL
{
	class Polygon
	{
		vector<GL::Vertex> vertices;
		bool isLooped;
	public:
		Polygon();
		~Polygon();

		void AddVertex(int x, int y) { AddVertex(GL::Vertex(x, y)); }
		void AddVertex(GL::Vertex p);

		vector<GL::Vertex> GetVertices() { return vertices; }
		void SetVertices(vector<GL::Vertex> vv) { vertices = vv; }
		GL::Vertex GetVertex(int index) { return vertices[(index + vertices.size()) % vertices.size()]; }
		int VertCount() { return vertices.size(); }
		
		int CheckMouseNearVertice(int x, int y);
		int CheckMouseNearEdge(int x, int y);
		bool IsInside(int x, int y);
		bool Loop();
		bool IsLooped() { return isLooped; }

		void MoveVertex(int vertNum, int x, int y);
		void AddVertAtEdge(int n, int x, int y);
		void DeleteVert(int n);

		void MovePolygon(int xOffset, int yOffset);
		bool CheckConvex();
	private:
		double Distance(double x1, double y1, double x2, double y2);
		GL::Vertex LineIntersection(GL::LineCoefficients lc1, GL::LineCoefficients lc2);
	};
}

