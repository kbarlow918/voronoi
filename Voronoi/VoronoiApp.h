/////////////////////////////////////////////////////////////////////////////
// VoronoiApp.h : main header file for the Voronoi DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVoronoiApp
// See VoronoiApp.cpp for the implementation of this class
//

class CVoronoiApp : public CWinApp
{
public:
	CVoronoiApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
};
