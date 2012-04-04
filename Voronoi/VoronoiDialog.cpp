// VoronoiDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VoronoiApp.h"
#include "VoronoiDialog.h"


// CVoronoiDialog dialog

IMPLEMENT_DYNAMIC(CVoronoiDialog, CDialog)

CVoronoiDialog::CVoronoiDialog(CWnd* pParent /*=NULL*/)
	: CRhinoDialog(CVoronoiDialog::IDD, pParent)
{

}

CVoronoiDialog::~CVoronoiDialog()
{
}

void CVoronoiDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editControl);
	DDX_Control(pDX, IDC_STRENGTH, m_editStrength);
	DDX_Control(pDX, IDC_OVERALLSTRENGTH, m_editOverallStrength);
	DDX_Control(pDX, IDC_CELL_LINES, CellLines);
}


BEGIN_MESSAGE_MAP(CVoronoiDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CVoronoiDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CVoronoiDialog::OnBnClickedAddAttractor)
	ON_BN_CLICKED(IDC_DELATTRACTOR, &CVoronoiDialog::OnBnClickedDelattractor)
	ON_BN_CLICKED(IDC_ADDCURVE, &CVoronoiDialog::OnBnClickedAddcurve)
	ON_BN_CLICKED(IDCLEAR, &CVoronoiDialog::OnBnClickedClear)
	ON_BN_CLICKED(IDC_VIEWEDIT, &CVoronoiDialog::OnBnClickedViewedit)
	ON_BN_CLICKED(IDC_CELL_GENERATE, &CVoronoiDialog::OnBnClickedCellGenerate)
	ON_BN_CLICKED(IDC_SHOWHIDE, &CVoronoiDialog::OnBnClickedShowhide)
END_MESSAGE_MAP()


// CVoronoiDialog message handlers

void CVoronoiDialog::OnBnClickedOk()
{
	ON_wString cmd = L"! _RandomPoint ";
	CString num;
	m_editControl.GetWindowText(num);
	cmd += (LPCTSTR)num;
	cmd += (LPCTSTR)" ";
	m_editOverallStrength.GetWindowText(num);
	cmd += (LPCTSTR)num;

	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnBnClickedAddAttractor()
{
	// TODO: Add your control notification handler code here
	ON_wString cmd = L"! _AddPtAttractor ";
	CString num;
	m_editStrength.GetWindowText(num);
	cmd += (LPCTSTR)num;

	//GetWindowText(; 
	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnBnClickedDelattractor()
{
	ON_wString cmd = L"! _DelPtAttractor ";

	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnBnClickedAddcurve()
{
	ON_wString cmd = L"! _AddCurveAttractor ";
	CString num;
	m_editStrength.GetWindowText(num);
	cmd += (LPCTSTR)num;

	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnBnClickedClear()
{
	ON_wString cmd = L"! _ClearAll ";

	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnBnClickedViewedit()
{
	ON_wString cmd = L"! _ViewEdit ";

	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnBnClickedCellGenerate()
{
	ON_wString cmd = L"! _RunVoronoi ";
	if(CellLines.GetState())
		cmd += (LPCTSTR)"1";
	else
		cmd += (LPCTSTR)"0";

	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnBnClickedShowhide()
{
	ON_wString cmd = L"! _TogglePtHide ";
	if(CellLines.GetState())
		cmd += (LPCTSTR)"1";
	else
		cmd += (LPCTSTR)"0";

	RhinoApp().RunScript( cmd , 0 );
}
