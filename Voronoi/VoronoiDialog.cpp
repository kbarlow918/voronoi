// VoronoiDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VoronoiApp.h"
#include "VoronoiDialog.h"
#include "VoronoiPlugIn.h"

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
	DDX_Control(pDX, IDC_EDIT1, points_NumPointEdit);
	DDX_Control(pDX, IDC_STRENGTH, attractor_StrengthEdit);
	DDX_Control(pDX, IDC_CELL_LINES, voronoi_DrawCellLines);
	DDX_Control(pDX, IDC_BUTTON1, attractor_AddPtAttractorButton);
	DDX_Control(pDX, IDC_ADDCURVE, attractor_AddCrvAttractorButton);
	DDX_Control(pDX, IDC_VIEWEDIT, attractor_ViewEditAttractorButton);
	DDX_Control(pDX, IDC_DELATTRACTOR, attractor_DeleteAttractorButton);
	DDX_Control(pDX, IDC_AttractorStrengthLabel, attractor_StrengthLabel);
	DDX_Control(pDX, IDOK, points_GenerateButton);
	DDX_Control(pDX, IDC_CLEAR_POINTS, points_ClearPointsButton);
	DDX_Control(pDX, IDC_NumPointsLabel, points_NumPtsLabel);
	DDX_Control(pDX, IDC_OverallStrengthLabel, points_OverallStrengthLabel);
	DDX_Control(pDX, IDC_VORONOI_MIN_DIST, voronoi_MinDistEdit);
	DDX_Control(pDX, IDC_INNER_CURVES, voronoi_InnerCurveOffsetEdit);
	DDX_Control(pDX, IDC_CELL_GENERATE, voronoi_GenerateButton);
	DDX_Control(pDX, IDC_SHOWHIDE, voronoi_ShowHideButton);
	DDX_Control(pDX, IDC_UNDO_CURVES, voronoi_UndoCurvesButton);
	DDX_Control(pDX, IDC_MinDistLabel, voronoi_MinDistLabel);
	DDX_Control(pDX, IDC_CurveOffsetLabel, voronoi_CurveOffsetLabel);
	DDX_Control(pDX, IDC_TRIM, trim_TrimButton);
	DDX_Control(pDX, IDC_UNDO_TRIM, trim_UndoTrimButton);
	DDX_Control(pDX, IDC_STRENGTH_SLIDER, points_strength_slider);
	DDX_Control(pDX, IDC_INDVSTRENGTH_SLIDER, attractor_strength_slider);

	SetState(POINT_GENERATION);

	//default values
	attractor_StrengthEdit.SetWindowTextW(L"70");
	points_NumPointEdit.SetWindowTextW(L"50");
	voronoi_InnerCurveOffsetEdit.SetWindowTextW(L"0.05");
	voronoi_MinDistEdit.SetWindowTextW(L"0.001");

	points_strength_slider.SetRangeMin(0);
	points_strength_slider.SetRangeMax(100, true);
	points_strength_slider.SetPos(50);
	attractor_strength_slider.SetRange(-100, 100, true);
	attractor_strength_slider.SetPos(70);
	
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
	ON_BN_CLICKED(IDC_UNDO_CURVES, &CVoronoiDialog::OnBnClickedUndoCurves)
	ON_BN_CLICKED(IDC_CLEAR_POINTS, &CVoronoiDialog::OnBnClickedClearPoints)
	ON_BN_CLICKED(IDC_BURN, &CVoronoiDialog::OnBnClickedBurn)
	ON_BN_CLICKED(IDC_HELP, &CVoronoiDialog::OnBnClickedHelp)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_INDVSTRENGTH_SLIDER, &CVoronoiDialog::OnNMReleasedcaptureIndvstrengthSlider)
	ON_BN_CLICKED(IDC_TRIM, &CVoronoiDialog::OnBnClickedTrim)
END_MESSAGE_MAP()


void CVoronoiDialog::DisableAll()
{
	bool val = false;

	attractor_AddPtAttractorButton.EnableWindow(val);
	attractor_AddCrvAttractorButton.EnableWindow(val);
	attractor_ViewEditAttractorButton.EnableWindow(val);
	attractor_DeleteAttractorButton.EnableWindow(val);
	attractor_StrengthEdit.EnableWindow(val);
	attractor_StrengthLabel.EnableWindow(val);
	attractor_strength_slider.EnableWindow(val);

	points_strength_slider.EnableWindow(val);
	points_NumPointEdit.EnableWindow(val);
	points_GenerateButton.EnableWindow(val);
	points_ClearPointsButton.EnableWindow(val);
	points_NumPtsLabel.EnableWindow(val);
	points_OverallStrengthLabel.EnableWindow(val);

	voronoi_MinDistEdit.EnableWindow(val);
	voronoi_InnerCurveOffsetEdit.EnableWindow(val);
	voronoi_GenerateButton.EnableWindow(val);
	voronoi_ShowHideButton.EnableWindow(val);
	voronoi_UndoCurvesButton.EnableWindow(val);
	voronoi_MinDistLabel.EnableWindow(val);
	voronoi_CurveOffsetLabel.EnableWindow(val);
	voronoi_DrawCellLines.EnableWindow(val);

	trim_TrimButton.EnableWindow(val);
	trim_UndoTrimButton.EnableWindow(val);
}

void CVoronoiDialog::SetState(int state)
{
	DisableAll();
	switch(state)
	{
	case VORONOI_GENERATION:
		points_ClearPointsButton.EnableWindow(true);
		voronoi_MinDistEdit.EnableWindow(true);
		voronoi_InnerCurveOffsetEdit.EnableWindow(true);
		voronoi_GenerateButton.EnableWindow(true);
		voronoi_MinDistLabel.EnableWindow(true);
		voronoi_CurveOffsetLabel.EnableWindow(true);
		voronoi_DrawCellLines.EnableWindow(true);
		break;
	case TRIM:
		voronoi_DrawCellLines.EnableWindow(true);
		voronoi_ShowHideButton.EnableWindow(true);
		voronoi_UndoCurvesButton.EnableWindow(true);
		trim_TrimButton.EnableWindow(true);
		break;
	case DONE:
		trim_UndoTrimButton.EnableWindow(true);
		break;
	case POINT_GENERATION:
	default:
		attractor_AddPtAttractorButton.EnableWindow(true);
		attractor_AddCrvAttractorButton.EnableWindow(true);
		attractor_ViewEditAttractorButton.EnableWindow(true);
		attractor_DeleteAttractorButton.EnableWindow(true);
		attractor_StrengthEdit.EnableWindow(true);
		attractor_StrengthLabel.EnableWindow(true);
		attractor_strength_slider.EnableWindow(true);
		points_strength_slider.EnableWindow(true);
		points_NumPointEdit.EnableWindow(true);
		points_GenerateButton.EnableWindow(true);
		points_NumPtsLabel.EnableWindow(true);
		points_OverallStrengthLabel.EnableWindow(true);
		break;
	}
}

// CVoronoiDialog message handlers

void CVoronoiDialog::OnBnClickedOk()
{
	ON_wString cmd = L"! _RandomPoint ";
	CString num;
	points_NumPointEdit.GetWindowText(num);
	cmd += (LPCTSTR)num;
	cmd += (LPCTSTR)" ";
	int pos = points_strength_slider.GetPos();
	num.Format(_T("%d"), pos);
	cmd += (LPCTSTR)num;

	RhinoApp().RunScript( cmd , 0 );
	SetState(VORONOI_GENERATION);
}

void CVoronoiDialog::OnBnClickedAddAttractor()
{
	// TODO: Add your control notification handler code here
	ON_wString cmd = L"! _AddPtAttractor ";
	CString num;
	attractor_StrengthEdit.GetWindowText(num);
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
	attractor_StrengthEdit.GetWindowText(num);
	cmd += (LPCTSTR)num;

	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnBnClickedClear()
{
	ON_wString cmd = L"! _ClearAll ";

	RhinoApp().RunScript( cmd , 0 );
	SetState(POINT_GENERATION);
}

void CVoronoiDialog::OnBnClickedViewedit()
{
	ON_wString cmd = L"! _ViewEdit ";

	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnBnClickedCellGenerate()
{
	ON_wString cmd = L"! _RunVoronoi ";
	CString num;
	voronoi_MinDistEdit.GetWindowText(num);
	cmd += (LPCTSTR)num;
	cmd += " ";
	voronoi_InnerCurveOffsetEdit.GetWindowText(num);
	cmd += (LPCTSTR)num;
	cmd += " ";
	if(voronoi_DrawCellLines.GetState())
		cmd += (LPCTSTR)"1";
	else
		cmd += (LPCTSTR)"0";

	RhinoApp().RunScript( cmd , 0 );
	SetState(TRIM);
}

void CVoronoiDialog::OnBnClickedShowhide()
{
	ON_wString cmd = L"! _TogglePtHide ";
	if(voronoi_DrawCellLines.GetState())
		cmd += (LPCTSTR)"1";
	else
		cmd += (LPCTSTR)"0";

	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnBnClickedUndoCurves()
{
	ON_wString cmd = L"! _UndoCurves ";
	RhinoApp().RunScript( cmd , 0 );
	SetState(VORONOI_GENERATION);
}

void CVoronoiDialog::OnBnClickedClearPoints()
{
	ON_wString cmd = L"! _UndoPoints ";
	RhinoApp().RunScript( cmd , 0 );
	SetState(POINT_GENERATION);
}

void CVoronoiDialog::OnBnClickedBurn()
{
	ON_wString cmd = L"! _BurnData ";
	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnBnClickedHelp()
{
	ON_wString cmd = L"! _HelpDlg ";
	RhinoApp().RunScript( cmd , 0 );
}

void CVoronoiDialog::OnNMReleasedcaptureIndvstrengthSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	int pos = attractor_strength_slider.GetPos();
	CString num;
	num.Format(_T("%d"), pos);
	attractor_StrengthEdit.SetWindowTextW(num);
}

void CVoronoiDialog::OnBnClickedTrim()
{
	ON_wString cmd = L"! _TrimBrep ";
	RhinoApp().RunScript( cmd , 0 );
}
