#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "My2DObjectA6.h"
#include "My2DPoint.h"

using namespace std;

#define PI 3.14159265

CMy2DObjectA6::CMy2DObjectA6(void):A(400),A1(100),A2(100),A3(100), m_dAngle(0)
{
	m_Center = CMy2DPoint(300, 300);
}

CMy2DObjectA6::CMy2DObjectA6(double a, double a1, double a2, double a3, const CMy2DPoint& center, double angle)
{
	if (a <= a1 + a2 + a3 || a1 >= a / 2 || a2 >= a / 2 || a3 >= a / 2)
	{
		cout << "Unable to create object! (" << a << ", " << a1 << ", " << a2 << ", " << a3 << ", ...)" << endl;
	}
	else
	{
		A = a;
		A1 = a1;
		A2 = a2;
		A3 = a3;
		m_Center = center;
		m_dAngle = angle;
	}
}

CMy2DObjectA6::CMy2DObjectA6(double a, double a1, double a2, double a3, double x, double y, double angle)
{
	if (a <= a1 + a2 + a3 || a1 >= a / 2 || a2 >= a / 2 || a3 >= a / 2)
	{
		cout << "Unable to create object! (" << a << ", " << a1 << ", " << a2 << ", " << a3 << ", ...)" << endl;
	}
	else
	{
		A = a;
		A1 = a1;
		A2 = a2;
		A3 = a3;
		m_Center = CMy2DPoint(x, y);
		m_dAngle = angle;
	}
	
}


CMy2DObjectA6::~CMy2DObjectA6(void)
{
}

double CMy2DObjectA6::GetA() const { return A; }
double CMy2DObjectA6::GetA1() const { return A1; }
double CMy2DObjectA6::GetA2() const { return A2; }
double CMy2DObjectA6::GetA3() const { return A3; }
CMy2DPoint CMy2DObjectA6::GetCenter() const { return m_Center; }
double CMy2DObjectA6::GetAngle() const { return m_dAngle; }

int CMy2DObjectA6::SetA(double a)
{
	if (a <= A1 + A2 + A3)
	{
		cout << "Unable to set A to '" << a << "'. Too small.";
		return -1;
	}
	else
		A = a;
	return 0;
}
int CMy2DObjectA6::SetA1(double a1)
{
	if (a1 >= A / 2)
	{
		cout << "Unable to set A1 to '" << a1 << "'. Too big.";
		return -1;
	}
	else
		A1 = a1;
	return 0;
}
int CMy2DObjectA6::SetA2(double a2)
{
	if (a2 >= A / 2)
	{
		cout << "Unable to set A2 to '" << a2 << "'. Too big.";
		return -1;
	}
	else
		A2 = a2;
	return 0;
}
int CMy2DObjectA6::SetA3(double a3)
{
	if (a3 >= A / 2)
	{
		cout << "Unable to set A3 to '" << a3 << "'. Too big.";
		return -1;
	}
	else
		A3 = a3;
	return 0;
}
int CMy2DObjectA6::SetCenter(const CMy2DPoint& center)
{
	m_Center = center;
	return 0;
}
int CMy2DObjectA6::SetAngle(double angle)
{
	m_dAngle = angle;
	if (m_dAngle >= 360)
		m_dAngle = m_dAngle - (int)(m_dAngle / 360) * 360;
	return 0;
}

void CMy2DObjectA6::Move(double dX, double dY, double dAngle)
{
	CMy2DPoint new_center(m_Center.GetX() + dX, m_Center.GetY() + dY);	
	m_Center = new_center;
	
	if (dAngle != 0)
	{
		m_dAngle = m_dAngle + dAngle;
		if (m_dAngle >= 360)
			m_dAngle = m_dAngle - (int)(m_dAngle / 360) * 360;
	}
	
}

void CMy2DObjectA6::Move(const CMy2DPoint &delta, double dAngle)
{
	Move(delta.GetX(), delta.GetY(), dAngle);
}

void CMy2DObjectA6::Rotate(double dAngle)
{
	m_dAngle += dAngle;
	if (m_dAngle >= 360 || m_dAngle <= 360)
		m_dAngle = m_dAngle - (int)(m_dAngle / 360) * 360;
}

bool CMy2DObjectA6::IsInside(const CMy2DPoint &point) const
{
	return IsInside(point.GetX(), point.GetY());
}

bool CMy2DObjectA6::IsInside(double x, double y) const
{
	// Новая система координат
	// nX = (x - x0) * cos(a) - (y - y0) * sin(a);
	// nY = (y - y0) * cos(a) + (x - x0) * sin(a);
	// x0, y0 - координаты центра фигуры

	// В нашем случае инвертируем Y, т.е. (y - y0) -> (y0 - y), т.к. ось Y в окнах перевернутая
	// Угол с минусом, т.к. крутим мы по часовой стрелке
	double fangle = -(double)m_dAngle / 180.0 * PI;
	float nX = (float)(cos(fangle)*(x - m_Center.GetX()) - sin(fangle)*(m_Center.GetY() - y));
	float nY = (float)(cos(fangle)*(m_Center.GetY() - y) + sin(fangle)*(x - m_Center.GetX()));

	// Проверяем вхождение в область
	if(nX < A/2 && nX > -A / 2)							// квадрат
		if(nY < A / 2 && nY > -A / 2)
			if (pow(nX - A / 2, 2) + pow(nY, 2) > pow(A1, 2))  // окружность A1 (справа)
			{
				if (nX < -A / 2 + A2 && nY > A / 2 - A2)	// Окружность сверху слева A2
					if (pow(nX + A / 2 - A2, 2) + pow(nY - A / 2 + A2, 2) < pow(A2, 2))
						return true;
					else
						return false;
				if (nX < -A / 2 + A3 && nY < -A / 2 + A3)	// Окружность снизу слева A3
					if (pow(nX + A / 2 - A3, 2) + pow(nY + A / 2 - A3, 2) < pow(A3, 2))
						return true;
					else
						return false;
				return true;
			}

	return false;
}

int Nx(double x, double y, double fangle, double c_x, double c_y)
{

	//return (float)(cos(fangle)*(x - c_x) - sin(fangle)*(c_y - y));
	//return x + (float)(c_x - cos(fangle)*c_x + sin(fangle)*c_y);
	return (int)(cos(fangle)*x - sin(fangle)*y - c_x*(cos(fangle) - 1) + c_y*sin(fangle));
}

int Ny(double x, double y, double fangle, double c_x, double c_y)
{
	//return (float)(cos(fangle)*(c_y - y) + sin(fangle)*(x - c_x));
	//return y + (float)(c_y - cos(fangle)*c_y - sin(fangle)*c_x);
	return (int)(cos(fangle)*y + sin(fangle)*x - c_x*sin(fangle) - c_y*(cos(fangle) - 1));
}

void CMy2DObjectA6::Draw(CDC &dc)
{
	double fangle = -(double)m_dAngle / 180 * PI;

	double x = m_Center.GetX() + A / 2;
	double y = m_Center.GetY() - A / 2;
	dc.MoveTo(Nx(x, y, fangle, m_Center.GetX(), m_Center.GetY()), Ny(x, y, fangle, m_Center.GetX(), m_Center.GetY()));

	x = m_Center.GetX() - A / 2 + A2;
	y = m_Center.GetY() - A / 2;
	dc.LineTo(Nx(x, y, fangle, m_Center.GetX(), m_Center.GetY()), Ny(x, y, fangle, m_Center.GetX(), m_Center.GetY()));

	x = m_Center.GetX() - A / 2 + A2;
	y = m_Center.GetY() - A / 2 + A2;
	dc.AngleArc(Nx(x, y, fangle, m_Center.GetX(), m_Center.GetY()), Ny(x, y, fangle, m_Center.GetX(), m_Center.GetY()), (int)A2, (float)(90 + m_dAngle), 90.0);

	x = m_Center.GetX() - A / 2;
	y = m_Center.GetY() + A / 2 - A3;
	dc.LineTo(Nx(x, y, fangle, m_Center.GetX(), m_Center.GetY()), Ny(x, y, fangle, m_Center.GetX(), m_Center.GetY()));

	x = m_Center.GetX() - A / 2 + A3;
	y = m_Center.GetY() + A / 2 - A3;
	dc.AngleArc(Nx(x, y, fangle, m_Center.GetX(), m_Center.GetY()), Ny(x, y, fangle, m_Center.GetX(), m_Center.GetY()), (int)A3, (float)(180 + m_dAngle), 90.0);

	x = m_Center.GetX() + A / 2;
	y = m_Center.GetY() + A / 2;
	dc.LineTo(Nx(x, y, fangle, m_Center.GetX(), m_Center.GetY()), Ny(x, y, fangle, m_Center.GetX(), m_Center.GetY()));

	x = m_Center.GetX() + A / 2;
	y = m_Center.GetY() + A1;
	dc.LineTo(Nx(x, y, fangle, m_Center.GetX(), m_Center.GetY()), Ny(x, y, fangle, m_Center.GetX(), m_Center.GetY()));

	x = m_Center.GetX() + A / 2;
	y = m_Center.GetY();
	dc.AngleArc(Nx(x, y, fangle, m_Center.GetX(), m_Center.GetY()), Ny(x, y, fangle, m_Center.GetX(), m_Center.GetY()), (int)A1, float(-90 + m_dAngle), -180.0);

	x = m_Center.GetX() + A / 2;
	y = m_Center.GetY() - A / 2;
	dc.LineTo(Nx(x, y, fangle, m_Center.GetX(), m_Center.GetY()), Ny(x, y, fangle, m_Center.GetX(), m_Center.GetY()));
}
