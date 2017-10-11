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
	/*
	bool operator==(const GL::Point & p1, const GL::Point & p2)
	{
	return ((p1.x==p2.x)&& (p1.y==p2.y));
	}
	bool operator!=(const GL::Point & p1, const GL::Point & p2)
	{
	return !(p1==p2);
	}*/
}
