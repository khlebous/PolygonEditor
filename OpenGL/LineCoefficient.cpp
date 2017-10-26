#include "LineCoefficient.h"

GL::LineCoefficients::LineCoefficients()
{
}

GL::LineCoefficients::LineCoefficients(int _a, int _b, int _c)
{
	A = _a;
	B = _b;
	C = _c;
}

GL::LineCoefficients::LineCoefficients(GL::Vertex v1, GL::Vertex v2)
{
	A = v2.GetY() - v1.GetY();
	B = v1.GetX() - v2.GetX();
	C = A*v1.GetX() + B*v1.GetY();
}

GL::LineCoefficients GL::LineCoefficients::FindParallelLine(int x, int y)
{
	int c = (A*x + B*y);
	return GL::LineCoefficients(A, B, c);
}
