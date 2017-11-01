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

bool GL::Point::operator==(Point & p) const
{
	return ((x==p.x)&&(y==p.y));
}
bool GL::Point::operator!=(Point & p) const
{
	return ((x != p.x) || (y != p.y));
}

