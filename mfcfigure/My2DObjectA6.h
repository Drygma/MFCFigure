#pragma once
#include "My2DPoint.h"


class CMy2DObjectA6
{
	double A, A1, A2, A3;
	CMy2DPoint m_Center;
	double m_dAngle;
	int r, g, b;
public:
	CMy2DObjectA6(void);
	CMy2DObjectA6(double a, double a1, double a2, double a3, const CMy2DPoint& center, double m_Angle);
	CMy2DObjectA6(double a, double a1, double a2, double a3, double x, double y, double angle);
	~CMy2DObjectA6(void);

	double GetA() const;
	double GetA1() const;
	double GetA2() const;
	double GetA3() const;
	CMy2DPoint GetCenter() const;
	double GetAngle() const;

	int SetA(double a);
	int SetA1(double A1);
	int SetA2(double A2);
	int SetA3(double A3);
	int SetCenter(const CMy2DPoint& center);
	int SetAngle(double angle);
	int SetColor(int R, int G, int B);

	// �������� ������� �� ������ dX, dY � ������� �� dAngle
	void Move(double dX, double dY, double dAngle = 0);
	// �������� ������� �� ������ ������ � ������� �� dAngle
	void Move(const CMy2DPoint &delta, double dAngle = 0);
	// ������� ������ �� ���� dAngle
	void Rotate(double dAngle);
	// ���������� true ���� ����� � ������������ (x,y) ����� ������ ������ � false � ��������� ������
	bool IsInside(double x, double y) const;
	// ���������� true ���� ����� ����� ������ ������ � false � ��������� ������
	bool IsInside(const CMy2DPoint &point) const;

	void Draw(CDC &dc);

};
