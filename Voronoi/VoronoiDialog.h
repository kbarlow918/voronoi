#pragma once

#include "Resource.h"
#include "afxwin.h"
#include "afxcmn.h"
// CVoronoiDialog dialog

#define POINT_GENERATION	0
#define	VORONOI_GENERATION	1
#define	TRIM				2
#define	DONE				3

class CVoronoiDialog : public CRhinoDialog
{
	DECLARE_DYNAMIC(CVoronoiDialog)

public:
	CVoronoiDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVoronoiDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();	
	afx_msg void OnBnClickedAddAttractor();
	afx_msg void OnBnClickedDelattractor();
	afx_msg void OnBnClickedAddcurve();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedViewedit();
	afx_msg void OnBnClickedCellGenerate();
	afx_msg void OnBnClickedShowhide();
private:
	CButton attractor_AddPtAttractorButton;
	CButton attractor_AddCrvAttractorButton;
	CButton attractor_ViewEditAttractorButton;
	CButton attractor_DeleteAttractorButton;
	CEdit attractor_StrengthEdit;
	CStatic attractor_StrengthLabel;

	CSliderCtrl points_strength_slider;
	CEdit points_NumPointEdit;
	CButton points_GenerateButton;
	CButton points_ClearPointsButton;
	CStatic points_NumPtsLabel;
	CStatic points_OverallStrengthLabel;

	CEdit voronoi_MinDistEdit;
	CEdit voronoi_InnerCurveOffsetEdit;
	CButton voronoi_GenerateButton;
	CButton voronoi_ShowHideButton;
	CButton voronoi_UndoCurvesButton;
	CStatic voronoi_MinDistLabel;
	CStatic voronoi_CurveOffsetLabel;
	CButton voronoi_DrawCellLines;

	CButton trim_TrimButton;
	CButton trim_UndoTrimButton;

	void DisableAll();
	void SetState(int state);
public:
	afx_msg void OnBnClickedUndoCurves();
	afx_msg void OnBnClickedClearPoints();
	afx_msg void OnBnClickedBurn();
	
	CSliderCtrl attractor_strength_slider;
	afx_msg void OnNMReleasedcaptureIndvstrengthSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedTrim();
	afx_msg void OnBnClickedUndoTrim();
	afx_msg void OnBnClickedClose();
};
