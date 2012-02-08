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
}


BEGIN_MESSAGE_MAP(CVoronoiDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CVoronoiDialog::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CVoronoiDialog::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CVoronoiDialog message handlers

void CVoronoiDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	ON_wString cmd = L"! _RandomPoint ";
	CString num;
	m_editControl.GetWindowText(num);
	cmd += (LPCTSTR)num;

	//GetWindowText(; 
	RhinoApp().RunScript( cmd , 0 );
	OnOK();
}

void CVoronoiDialog::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CRhinoDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
