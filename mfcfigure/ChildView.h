
// ChildView.h : ��������� ������ CChildView
//


#pragma once

#include "My2DPoint.h"
#include "My2DObjectA6.h"
#include <vector>

// ���� CChildView

class CChildView : public CWnd
{
// ��������
public:
	CChildView();

// ��������
public:
protected:
	std::vector<CMy2DObjectA6 *> m_Objects;
	int num_of_objects;
	CPoint m_MousePos;
	int m_nCatched;

// ��������
public:
	int FindObject(CPoint point);

// ���������������
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����������
public:
	virtual ~CChildView();

	// ��������� ������� ����� ���������
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnNewFigure();
};

