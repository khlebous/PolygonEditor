#pragma once
namespace GL
{
	struct  Point
	{
		int x, y;
		Point();
		Point(int _x, int _y);
		Point(const Point& p);
		bool Point::operator==(const Point &p);
		bool Point::operator!=(const Point &p);
	};
}
