// DlgProperties.cpp: файл реализации
//

#include "stdafx.h"
#include "MFCFigure.h"
#include "DlgProperties.h"
#include "afxdialogex.h"


// диалоговое окно CDlgProperties

IMPLEMENT_DYNAMIC(CDlgProperties, CDialogEx)

CDlgProperties::CDlgProperties(CWnd* pParent /*=NULL*/, int nX, int nY, 
	double dA, double dA1, double dA2, double dA3, double dAngle)
	: CDialogEx(IDD_PROPERTIES, pParent)
	, m_nX(nX)
	, m_nY(nY)
	, m_dA(dA)
	, m_dA1(dA1)
	, m_dA2(dA2)
	, m_dA3(dA3)
	, m_dAngle(dAngle)
	, OK(false)
{

}

CDlgProperties::~CDlgProperties()
{
}

void CDlgProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_E_X, m_nX);
	DDX_Text(pDX, IDC_E_Y, m_nY);
	DDX_Text(pDX, IDC_E_A, m_dA);
	DDX_Text(pDX, IDC_E_A1, m_dA1);
	DDX_Text(pDX, IDC_E_A2, m_dA2);
	DDX_Text(pDX, IDC_E_A3, m_dA3);
	DDX_Text(pDX, IDC_E_ANG, m_dAngle);
}


BEGIN_MESSAGE_MAP(CDlgProperties, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgProperties::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgProperties::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CDlgProperties::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;

	str.Format(_T("%d"), m_nX);
	SetDlgItemText(IDC_E_X, str);

	str.Format(_T("%d"), m_nY);
	SetDlgItemText(IDC_E_Y, str);

	str.Format(_T("%.2lf"), m_dA);
	SetDlgItemText(IDC_E_A, str);

	str.Format(_T("%.2lf"), m_dA1);
	SetDlgItemText(IDC_E_A1, str);

	str.Format(_T("%.2lf"), m_dA2);
	SetDlgItemText(IDC_E_A2, str);

	str.Format(_T("%.2lf"), m_dA3);
	SetDlgItemText(IDC_E_A3, str);

	str.Format(_T("%.2lf"), m_dAngle);
	SetDlgItemText(IDC_E_ANG, str);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}


void CDlgProperties::OnBnClickedOk()
{
	OK = true;
	CDialogEx::OnOK();
}


void CDlgProperties::OnBnClickedCancel()
{
	OK = false;
	CDialogEx::OnCancel();
}
