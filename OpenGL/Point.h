#pragma once
namespace GL
{
	struct  Point
	{
		int x, y;
		Point();
		Point(int _x, int _y);
		Point(const Point& p);
	};
	bool operator==(const GL::Point & p1, const GL::Point & p2);
	bool operator!=(const GL::Point & p1, const GL::Point & p2);
}
