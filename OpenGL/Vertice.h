#pragma once
#include "Point.h"
#include <GL/glut.h> 

namespace GL
{
	//TODO Vetex
	class Vertice
	{
		int x;
		int y;

	public:
		Vertice();
		~Vertice();
		Vertice(int _x, int _y);
		Vertice(GL::Point p);

		void Draw();
		void HighlightVertice();
		void UnhighlightVertice();
		void Move(int x, int y);

		int GetX()const { return x; };
		int GetY()const { return y; }
		void SetX(int _x) { x = _x; }
		void SetY(int _y) { y = _y; }

		bool operator==(Vertice& v)const;
		bool operator!=(Vertice& v)const;
	};
	/*
	bool operator==(const GL::Vertice & v1, const GL::Vertice & v2)
	{
		if ((v1.GetX()==v2.GetX()) && (v1.GetY()==v2.GetY()))
			return true;
		else
			return false;
	}
	bool operator!=(const GL::Vertice & v1, const GL::Vertice & v2)
	{
		return !(v1 == v2);
	}*/
}