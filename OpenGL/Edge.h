#pragma once
#include <vector>
#include "Vertice.h"
#include "Point.h"

using namespace std;

namespace GL
{
	class Edge
	{
		vector<GL::Point> points;

	public:
		Edge();
		Edge(GL::Vertice v1, GL::Vertice v2);
		~Edge();

		void Draw();
		void Highlight();
		void Unhighlight();

		vector<GL::Point> GetPoints() const { return points; }
		bool IsPointNear(int x, int y, int maxDistance);
		int Length()const { return points.size(); }

		bool operator==(Edge& e)const;
		bool operator!=(Edge& e)const;
	};

	/*bool operator==(const GL::Edge & e1, const GL::Edge & e2)
	{
		
	}
	bool operator!=(const GL::Edge & p1, const GL::Edge & p2)
	{
		return !(p1 == p2);
	}*/
}
