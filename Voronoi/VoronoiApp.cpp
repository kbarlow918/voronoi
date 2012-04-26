/*
Voronoi Diagram Generator for Surfaces in Rhinoceros 3d
Copyright (C) 2012 Kevin Barlow, Stephen Sheafer and Joe Wolter

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA*/

/////////////////////////////////////////////////////////////////////////////
// VoronoiApp.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "VoronoiApp.h"

//
//	Note!
//
//    A Rhino plug-in is an MFC DLL.
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//


// CVoronoiApp

BEGIN_MESSAGE_MAP(CVoronoiApp, CWinApp)
	ON_BN_CLICKED(IDOK, &CVoronoiApp::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoronoiApp construction

CVoronoiApp::CVoronoiApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CVoronoiApp object
CVoronoiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVoronoiApp initialization

BOOL CVoronoiApp::InitInstance()
{

	CWinApp::InitInstance();

	return TRUE;
}

void CVoronoiApp::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	
}
