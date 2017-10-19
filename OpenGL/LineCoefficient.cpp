#include "LineCoefficient.h"

GL::LineCoefficients::LineCoefficients()
{
}

GL::LineCoefficients::LineCoefficients(GL::Vertex v1, GL::Vertex v2)
{
	A = v2.GetY() - v1.GetY();
	B = v1.GetX() - v2.GetX();
	C = A*v1.GetX() + B*v1.GetY();
}

void GL::LineCoefficients::ChangeCoefficientsToParallelLine(int x, int y)
{
	C = (A*x + B*y);
	//B = 1;
	//A /= B;
}
