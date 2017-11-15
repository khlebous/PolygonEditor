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
GL::Vertex GL::LineCoefficients::LineIntersection(GL::LineCoefficients lc1)
{
	int A1 = lc1.GetA();
	int B1 = lc1.GetB();
	int C1 = lc1.GetC();

	int A2 = A;
	int B2 = B;
	int C2 = C;

	double det = A1*B2 - A2*B1;

	if (det == 0)
	{
	}
	else
	{
		double x = (B2*C1 - B1*C2) / det;
		double y = (A1*C2 - A2*C1) / det;
		return GL::Vertex(round(x), round(y));
	}
	return GL::Vertex(-1, -1);
}