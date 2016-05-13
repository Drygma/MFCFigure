
// ChildView.cpp : реализация класса CChildView
//

#include "stdafx.h"
#include "MFCFigure.h"
#include "ChildView.h"
#include "DlgProperties.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.14159265

int Nx(double x, double y, double fangle, double c_x, double c_y);
int Ny(double x, double y, double fangle, double c_x, double c_y);

// CChildView

CChildView::CChildView()
{
	// Initialization
	m_nCatched = -1;
	m_nRightClicked = -1;
	num_of_objects = 0;
}

CChildView::~CChildView()
{
	for (int i = 0; m_Objects[i]; i++) {
		delete m_Objects[i];
	}

}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_NEWFIGURE, OnNewFigure)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_POPUP_EDIT, &CChildView::OnPopupEdit)
	ON_COMMAND(ID_POPUP_REMOVE, &CChildView::OnPopupRemove)
END_MESSAGE_MAP()



// обработчики сообщений CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // контекст устройства для рисования

	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CRect rect;
	GetClientRect(&rect);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap *pOldBmp = dcMem.SelectObject(&bmp);
	dcMem.FillSolidRect(0, 0, rect.Width(), rect.Height(), 0xFFFFFF); //0xFFFFFF = RGB(255, 255, 255)	
	for (int i = 0; i<m_Objects.size(); i++) {
		m_Objects[i]->Draw(dcMem); // рисуем каждый объект в память
	}

	// Показываем количество объектов
	CString str;
	str.Format(_T("Number of objects: %d\n"), num_of_objects);
	if (m_nCatched >= 0) // Если схватили объект, то показываем еще и координаты
	{
		CString str1;
		str1.Format(_T("Dragging object... (X: %.0lf | Y: %.0lf)"), 
			m_Objects[m_nCatched]->GetCenter().GetX(), m_Objects[m_nCatched]->GetCenter().GetY());
		str += str1;
	}
	// Рисуем текст в правом верхнем углу
	dcMem.DrawText(str, rect, DT_RIGHT);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, SRCCOPY);
	dcMem.SelectObject(pOldBmp);

	// Не вызывайте CWnd::OnPaint() для сообщений рисования
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_nCatched = FindObject(point);
	if (m_nCatched >= 0) {
		m_MousePos = point;
		SetCapture();
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_nCatched >= 0) {
		CRect rect;
		GetClientRect(&rect);
		point.x = min(rect.right, max(rect.left, point.x));
		point.y = min(rect.bottom, max(rect.top, point.y));
		CPoint Delta = point - m_MousePos;
		m_Objects[m_nCatched]->Move(Delta.x, Delta.y);
		m_MousePos = point;
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_nCatched = -1;
	ReleaseCapture();
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (m_nCatched >= 0) {
		m_Objects[m_nCatched]->Rotate(zDelta / 45);
		Invalidate();
	}

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CChildView::OnNewFigure() {
	
	srand(time(NULL));

	CRect rect;
	GetClientRect(&rect);
	m_Objects.push_back(new CMy2DObjectA6());
	m_Objects.back()->SetColor(rand() % 253 + 1, rand() % 253 + 1, rand() % 253 + 1);
	num_of_objects++;
	Invalidate();
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC) {
	//Don’t call base class implementation 
	//return CWnd::OnEraseBkgnd(pDC);
	return true;//Just return true.
}

int CChildView::FindObject(CPoint point) {
	int nObj = -1; // if none object found, return -1
	for (int i = m_Objects.size() - 1; i >= 0; i--) {
		if (m_Objects[i]->IsInside(point.x, point.y)) {
			nObj = i;
			break;
		}
	}
	return nObj;
}

void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	m_nCatched = FindObject(point);
	if (m_nCatched >= 0) {
		bool OK = false;
		// При двойном щелчке по объекту, открываем окно редактирования параметров
		while (!OK)
		{
			if (OK) break;

			CMy2DObjectA6 *selected_object = m_Objects[m_nCatched];
			CDlgProperties dlg(
				NULL,
				selected_object->GetCenter().GetX(),
				selected_object->GetCenter().GetY(),
				selected_object->GetA(),
				selected_object->GetA1(),
				selected_object->GetA2(),
				selected_object->GetA3(),
				selected_object->GetAngle());
			dlg.DoModal();
			if (dlg.OK)
			{	// Если пользователь нажал ОК, то меняем параметры фигуры и отрисовываем
				int oldX = selected_object->GetCenter().GetX();
				int oldY = selected_object->GetCenter().GetY();
				double oldAngle = selected_object->GetAngle();

				selected_object->Move(dlg.m_nX - oldX, dlg.m_nY - oldY, dlg.m_dAngle - oldAngle);
				// Если ошибка при изменении параметра, то вызываем окно еще раз
				if (selected_object->SetA1(dlg.m_dA1))
					continue;
				if (selected_object->SetA2(dlg.m_dA2))
					continue;
				if (selected_object->SetA3(dlg.m_dA3))
					continue;
				if (selected_object->SetA(dlg.m_dA))
					continue;

				OK = true;
				Invalidate();
			}
			else
				OK = true;
		}	
		m_nCatched = -1;
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_nRightClicked = FindObject(point);
	if (m_nRightClicked >= 0) {
		// При щелчке ПКМ по объекту, показываем контекстное меню
		CMenu menuFigure;
		menuFigure.LoadMenu(IDR_FIGURE_MENU);

		CMenu *mnuPopupMenu = menuFigure.GetSubMenu(0);
		ASSERT(mnuPopupMenu);

		CPoint p;
		GetCursorPos(&p);

		mnuPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, p.x, p.y, this);
	}

	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnPopupEdit()
{
	if (m_nRightClicked >= 0) {
		bool OK = false;
		// При щелчке по кнопке Edit, открываем окно редактирования параметров
		while (!OK)
		{
			if (OK) break;

			CMy2DObjectA6 *selected_object = m_Objects[m_nRightClicked];
			CDlgProperties dlg(
				NULL,
				selected_object->GetCenter().GetX(),
				selected_object->GetCenter().GetY(),
				selected_object->GetA(),
				selected_object->GetA1(),
				selected_object->GetA2(),
				selected_object->GetA3(),
				selected_object->GetAngle());
			dlg.DoModal();
			if (dlg.OK)
			{
				int oldX = selected_object->GetCenter().GetX();
				int oldY = selected_object->GetCenter().GetY();
				double oldAngle = selected_object->GetAngle();

				selected_object->Move(dlg.m_nX - oldX, dlg.m_nY - oldY, dlg.m_dAngle - oldAngle);
				// Если ошибка при изменении параметра, то вызываем окно еще раз
				if (selected_object->SetA1(dlg.m_dA1))
					continue;
				if (selected_object->SetA2(dlg.m_dA2))
					continue;
				if (selected_object->SetA3(dlg.m_dA3))
					continue;
				if (selected_object->SetA(dlg.m_dA))
					continue;

				OK = true;
				Invalidate();
			}
			else
				OK = true;
		}
		m_nRightClicked = -1;
	}
}


void CChildView::OnPopupRemove()
{
	if (m_nRightClicked >= 0) {
		// При щелчке по кнопке Remove, удаляем объект и перерисовываем
		m_Objects.erase(m_Objects.begin() + m_nRightClicked);
		num_of_objects--;
		Invalidate();
		m_nRightClicked = -1;
	}
}
