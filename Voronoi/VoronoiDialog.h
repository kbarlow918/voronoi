#pragma once

#include "Resource.h"
#include "afxwin.h"
// CVoronoiDialog dialog

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
	CEdit m_editControl;
	afx_msg void OnBnClickedAddAttractor();
	CEdit m_editStrength;
	CEdit m_editOverallStrength;
	afx_msg void OnBnClickedDelattractor();
	afx_msg void OnBnClickedAddcurve();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedViewedit();
	CButton CellLines;
	afx_msg void OnBnClickedCellGenerate();
	afx_msg void OnBnClickedShowhide();
};
