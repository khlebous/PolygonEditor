#pragma once
#include "LineCoefficient.h"

class SetAngle
{
	int n;
	float angle;

	GL::LineCoefficients left1;
	GL::LineCoefficients left2;
	GL::LineCoefficients right1;
	GL::LineCoefficients right2;

public:
	SetAngle();
	~SetAngle();

	SetAngle(const SetAngle& sa);
	SetAngle(int _n, int _angle, 
		GL::LineCoefficients _left1,
		GL::LineCoefficients _left2,
		GL::LineCoefficients _right1,
		GL::LineCoefficients _right2);

	int GetVertexNumber() { return n; }

	GL::LineCoefficients GetLC_L1() { return left1; }
	GL::LineCoefficients GetLC_L2() { return left2; }
	GL::LineCoefficients GetLC_R1() { return right1; }
	GL::LineCoefficients GetLC_R2() { return right2; }

	void SetLC_L1(GL::LineCoefficients lc) { left1 = lc; }
	void SetLC_L2(GL::LineCoefficients lc) { left2 = lc; }
	void SetLC_R1(GL::LineCoefficients lc) { right1 = lc; }
	void SetLC_R2(GL::LineCoefficients lc) { right2=lc; }

private:

};

