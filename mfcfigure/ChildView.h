
// ChildView.h : интерфейс класса CChildView
//


#pragma once

#include "My2DPoint.h"
#include "My2DObjectA6.h"
#include <vector>

// окно CChildView

class CChildView : public CWnd
{
// Создание
public:
	CChildView();

// Атрибуты
public:
protected:
	std::vector<CMy2DObjectA6 *> m_Objects;
	int num_of_objects;
	CPoint m_MousePos;
	int m_nCatched;
	int m_nRightClicked;

// Операции
public:
	int FindObject(CPoint point);

// Переопределение
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Реализация
public:
	virtual ~CChildView();

	// Созданные функции схемы сообщений
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
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPopupEdit();
	afx_msg void OnPopupRemove();
};

