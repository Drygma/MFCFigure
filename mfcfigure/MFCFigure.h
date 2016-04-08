
// MFCFigure.h : главный файл заголовка для приложения MFCFigure
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CMFCFigureApp:
// О реализации данного класса см. MFCFigure.cpp
//

class CMFCFigureApp : public CWinApp
{
public:
	CMFCFigureApp();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCFigureApp theApp;
