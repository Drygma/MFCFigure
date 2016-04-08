#pragma once

#include <ostream>
#include <istream>

class CMy2DPoint
{
	double x;
	double y;
public:
	CMy2DPoint(void);
	CMy2DPoint(double x, double y);
	~CMy2DPoint(void);

	double GetX() const;
	double GetY() const;

	CMy2DPoint operator=(const CMy2DPoint& point);
	CMy2DPoint operator+(const CMy2DPoint& point);
	CMy2DPoint operator-(const CMy2DPoint& point);
	
	CMy2DPoint operator*(const double mult);
	CMy2DPoint operator/(const double mult);
	friend double operator*(const CMy2DPoint& point1, const CMy2DPoint& point2);
	friend CMy2DPoint operator*(const double mult, const CMy2DPoint& point);

	friend std::ostream& operator<< (std::ostream& out, const CMy2DPoint& point);
	friend CMy2DPoint& operator>> (std::istream& in, CMy2DPoint& point);

	friend bool operator==(const CMy2DPoint& one, const CMy2DPoint& two);
	friend bool operator!=(const CMy2DPoint& one, const CMy2DPoint& two);

};

