#include "stdafx.h"
#include "My2DPoint.h"


CMy2DPoint::CMy2DPoint(void)
{
}

CMy2DPoint::CMy2DPoint(double x, double y): x(x), y(y) {}


CMy2DPoint::~CMy2DPoint(void)
{

}

double CMy2DPoint::GetX() const
{
	return x;
}

double CMy2DPoint::GetY() const
{
	return y;
}


CMy2DPoint CMy2DPoint::operator=(const CMy2DPoint& point)
{
	x = point.x;
	y = point.y;
	return *this;
}

CMy2DPoint CMy2DPoint::operator+(const CMy2DPoint& point)
{
	return CMy2DPoint((*this).x+point.x, (*this).y+point.y);
}

CMy2DPoint CMy2DPoint::operator-(const CMy2DPoint& point)
{
	return CMy2DPoint((*this).x-point.x, (*this).y-point.y);
}

CMy2DPoint CMy2DPoint::operator*(const double mult)
{
	return CMy2DPoint((*this).x*mult, (*this).y*mult);
}

double operator*(const CMy2DPoint& point1, const CMy2DPoint& point2)
{
	return point1.x*point2.x + point1.y*point2.y;
}

CMy2DPoint operator*(const double mult, const CMy2DPoint& point)
{
	return CMy2DPoint(point.x*mult, point.y*mult);
}

CMy2DPoint CMy2DPoint::operator/(const double mult)
{
	return CMy2DPoint((*this).x/mult, (*this).y/mult);
}

std::ostream& operator<< (std::ostream& out, const CMy2DPoint& point)
{
	out << "(" << point.x << " ; " << point.y << ")";
	return out;
}

CMy2DPoint& operator>> (std::istream& in, CMy2DPoint& point)
{
	in >> point.x;
	in >> point.y;
	return point;
}

bool operator==(const CMy2DPoint& one, const CMy2DPoint& two)
{
	return one.x == two.x && one.y == two.y;
}

bool operator!=(const CMy2DPoint& one, const CMy2DPoint& two)
{
	return !operator==(one, two);
}
