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
	afx_msg void OnEnChangeEdit1();
	CEdit m_editControl;
};
