#include "Point.h"

GL::Point::Point()
{
	x = 0;
	y = 0;
}

GL::Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;

}

GL::Point::Point(const GL::Point & p)
{
	x = p.x;
	y = p.y;
}

bool GL::operator==(const GL::Point & p1, const GL::Point & p2)
{
	return ((p1.x==p2.x)&& (p1.y==p2.y));
}

bool GL::operator!=(const GL::Point & p1, const GL::Point & p2)
{
	return !(p1==p2);
}
