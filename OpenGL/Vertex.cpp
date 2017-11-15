#include "Vertex.h"

GL::Vertex::Vertex()
{
	x = -1;
	y = -1;
}
GL::Vertex::~Vertex()
{
}
GL::Vertex::Vertex(int _x, int _y)
{
	x = _x;
	y = _y;
}

void GL::Vertex::Move(int _x, int _y)
{
	x = _x; 
	y = _y;
}

bool GL::Vertex::operator==(Vertex & v) const
{
	if ((x == v.GetX()) && (y == v.GetY()))
		return true;
	else
		return false;
}
bool GL::Vertex::operator!=(Vertex & v) const
{
	if ((x != v.GetX()) || (y != v.GetY()))
		return true;
	else
		return false;
}

GL::Vertex GL::Vertex::operator+(const Vertex &v) const
{
	GL::Vertex vOut = GL::Vertex();
	vOut.SetX(x + v.GetX());
	vOut.SetY(y + v.GetY());
	return vOut;
}

ostream & GL::operator<<(ostream & os, const Vertex & v)
{
	os << "("<<v.GetX()<<","<<v.GetY()<<")\n";
	return os;
}
