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
		LineCoefficients(GL::Vertex p1, GL::Vertex p2);

		int GetA() { return A; }
		int GetB() { return B; }
		int GetC() { return C; }

		void ChangeCoefficientsToParallelLine(int x, int y);
	};
}
