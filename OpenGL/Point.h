#pragma once
namespace GL
{
	struct  Point
	{
		int x, y;
		Point();
		Point(int _x, int _y);
		Point(const Point& p);
		bool operator==(Point& p)const;
		bool operator!=(Point& p)const;
	};
}
