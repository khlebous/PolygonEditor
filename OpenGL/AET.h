#pragma once
#include "Vertex.h"
namespace GL
{
	struct AET
	{
		GL::Vertex v1;
		GL::Vertex v2;
		float x;
		float m ;
		int ymax;

		AET(GL::Vertex _v1, GL::Vertex _v2)
		{
			v1 = _v1;
			v2 = _v2;
			x = v1.GetY() < v2.GetY() ? v1.GetX() : v2.GetX();
			m = (float)(v1.GetX() - v2.GetX()) / (float)(v1.GetY() - v2.GetY());
			ymax = v1.GetY() > v2.GetY() ? v1.GetY() : v2.GetY();
		}
		
		bool operator < (const AET& str) const
		{
			return (x<str.x);
		}
	};

}