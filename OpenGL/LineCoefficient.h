#pragma once
#include "Vertex.h"
namespace GL
{
	class LineCoefficients
	{
		int A;
		int B;
		int C;
	public:
		LineCoefficients();
		LineCoefficients(int _a, int _b, int _c);
		LineCoefficients(GL::Vertex p1, GL::Vertex p2);

		int GetA() { return A; }
		int GetB() { return B; }
		int GetC() { return C; }

		LineCoefficients FindParallelLine(int x, int y);
	};
}
