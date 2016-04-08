#pragma once

#include "My2DObjectA6.h"

// диалоговое окно CDlgProperties

class CDlgProperties : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProperties)

public:
	//конструктор
	CDlgProperties(CWnd* pParent, int m_nX, int m_nY,
		double m_dA, double m_dA1, double m_dA2, double m_dA3, double m_dAngle);
	virtual ~CDlgProperties();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_nX;
	int m_nY;
	double m_dA;
	double m_dA1;
	double m_dA2;
	double m_dA3;
	double m_dAngle;
	virtual BOOL OnInitDialog();
};
