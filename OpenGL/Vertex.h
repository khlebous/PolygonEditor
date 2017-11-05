#pragma once
#include "Point.h"
#include <GL/glut.h> 
#include <ostream>
using namespace std;
namespace GL
{
	//TODO Vetex
	class Vertex
	{
		int x;
		int y;


	public:
		int nr;
		Vertex();
		~Vertex();
		Vertex(int _x, int _y);
		Vertex(GL::Point p);

		void Move(int x, int y);

		int GetX()const { return x; };
		int GetY()const { return y; }
		void SetX(int _x) { x = _x; }
		void SetY(int _y) { y = _y; }

		bool operator==(Vertex& v)const;
		bool operator!=(Vertex& v)const;
		Vertex operator+(const Vertex&) const;
		friend ostream& operator<<(ostream& os, const Vertex& v);
	};
}