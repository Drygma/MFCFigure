
// MFCFigure.h : ������� ���� ��������� ��� ���������� MFCFigure
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CMFCFigureApp:
// � ���������� ������� ������ ��. MFCFigure.cpp
//

class CMFCFigureApp : public CWinApp
{
public:
	CMFCFigureApp();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCFigureApp theApp;
