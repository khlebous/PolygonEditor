#include "SetAngle.h"

SetAngle::SetAngle()
{
}

SetAngle::~SetAngle()
{
}

SetAngle::SetAngle(const SetAngle & sa)
{
	n = sa.n;
	angle = sa.angle;
	left2 = sa.left2;
	left1 = sa.left1;
	right1 = sa.right1;
	right2 = sa.right2;
}
SetAngle::SetAngle(int _n, int _angle, GL::LineCoefficients _left1, GL::LineCoefficients _left2, GL::LineCoefficients _right1, GL::LineCoefficients _right2)
{
	n = _n;
	angle = _angle;
	left1 = _left1;
	left2 = _left2;
	right1 = _right1;
	right2 = _right2;
}
