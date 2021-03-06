/////////////////////////////////////////////////////////////////////////////
// cmdVoronoi.cpp : command file
//

#include "StdAfx.h"
#include "VoronoiPlugIn.h"
#include "RndPointSet.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN Voronoi command
//

// Do NOT put the definition of class CCommandVoronoi in a header
// file.  There is only ONE instance of a CCommandVoronoi class
// and that instance is the static theVoronoiCommand that appears
// immediately below the class definition.

class CCommandVoronoi : public CRhinoCommand
{
public:
  // The one and only instance of CCommandVoronoi is created below.
  // No copy constructor or operator= is required.  Values of
  // member variables persist for the duration of the application.

  // CCommandVoronoi::CCommandVoronoi()
  // is called exactly once when static theVoronoiCommand is created.
	CCommandVoronoi() {}

  // CCommandVoronoi::~CCommandVoronoi()
  // is called exactly once when static theVoronoiCommand is
  // destroyed.  The destructor should not make any calls to
  // the Rhino SDK.  If your command has persistent settings,
  // then override CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandVoronoi() {}

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work.  Use GUIDGEN.EXE to make unique UUID.
	UUID CommandUUID()
	{
		// {4AF920C4-6016-477D-BD0C-6D8DBB7598D1}
    static const GUID VoronoiCommand_UUID =
    { 0x4AF920C4, 0x6016, 0x477D, { 0xBD, 0xC, 0x6D, 0x8D, 0xBB, 0x75, 0x98, 0xD1 } };
    return VoronoiCommand_UUID;
	}

	RndPointSet mySet;
	CVoronoiDialog *m_dialog;
  // Returns the English command name.
	const wchar_t* EnglishCommandName() { return L"Voronoi"; }

  // Returns the localized command name.
	const wchar_t* LocalCommandName() { return L"Voronoi"; }

  // Rhino calls RunCommand to run the command.
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandVoronoi object.  
// Do NOT create any other instance of a CCommandVoronoi class.
static class CCommandVoronoi theVoronoiCommand;

CRhinoCommand::result CCommandVoronoi::RunCommand( const CRhinoCommandContext& context )
{
  // CCommandVoronoi::RunCommand() is called when the user runs the "Voronoi"
  // command or the "Voronoi" command is run by a history operation.

  // TODO: Add command code here.

  // Rhino command that display a dialog box interface should also support
  // a command-line, or scriptable interface.
	m_dialog = new CVoronoiDialog( CWnd::FromHandle(RhinoApp().MainWnd()) );
	if( m_dialog->Create(IDD_DIALOG1, CWnd::FromHandle(RhinoApp().MainWnd())) )
	{
		m_dialog->ShowWindow( SW_SHOW );
		m_dialog->UpdateWindow();
		m_dialog->SetFocus();
	}
  
  /*
  {
	
  }
  {
  }
	 */ 

  // TODO: Return one of the following values:
  //   CRhinoCommand::success:  The command worked.
  //   CRhinoCommand::failure:  The command failed because of invalid input, inability
  //                            to compute the desired result, or some other reason
  //                            computation reason.
  //   CRhinoCommand::cancel:   The user interactively canceled the command 
  //                            (by pressing ESCAPE, clicking a CANCEL button, etc.)
  //                            in a Get operation, dialog, time consuming computation, etc.

  return CRhinoCommand::success;
}

//
// END Voronoi command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN RandomPoint command
//

class CCommandRandomPoint : public CRhinoTestCommand
{
public:
	CCommandRandomPoint() {}
	~CCommandRandomPoint() {}
	UUID CommandUUID()
	{
		// {A3E576E2-7A1F-42F9-8EFE-D0F92B17BAD8}
		static const GUID RandomPointCommand_UUID =
		{ 0xA3E576E2, 0x7A1F, 0x42F9, { 0x8E, 0xFE, 0xD0, 0xF9, 0x2B, 0x17, 0xBA, 0xD8 } };
		return RandomPointCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"RandomPoint"; }
	const wchar_t* LocalCommandName() { return L"RandomPoint"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandRandomPoint object
static class CCommandRandomPoint theRandomPointCommand;

CRhinoCommand::result CCommandRandomPoint::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
  CRhinoGetNumber gn;
  gn.SetDefaultNumber( 1 ) ;
  gn.AcceptNothing();
  gn.GetNumber();
  int rc = gn.CommandResult();

  CRhinoGetNumber gn2;
  gn2.SetDefaultNumber( 1.0 ) ;
  gn2.AcceptNothing();
  gn2.GetNumber();
  double rc2 = gn2.CommandResult();
	
  int arg1 = (int) gn.Number();
  double arg2 = gn2.Number();

  theVoronoiCommand.mySet.DrawPoints(context, arg1, arg2);
  //RhinoApp().Print("drawpoints with %d %f\n", arg1, arg2);
  return CRhinoCommand::success;
}

//
// END RandomPoint command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN AddPtAttractor command
//

class CCommandAddPtAttractor : public CRhinoCommand
{
public:
	CCommandAddPtAttractor() {}
	~CCommandAddPtAttractor() {}
	UUID CommandUUID()
	{
		// {7C0AE2D0-65F6-4677-B1EA-334A94B38C49}
		static const GUID AddPtAttractorCommand_UUID =
		{ 0x7C0AE2D0, 0x65F6, 0x4677, { 0xB1, 0xEA, 0x33, 0x4A, 0x94, 0xB3, 0x8C, 0x49 } };
		return AddPtAttractorCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"AddPtAttractor"; }
	const wchar_t* LocalCommandName() { return L"AddPtAttractor"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandAddPtAttractor object
static class CCommandAddPtAttractor theAddPtAttractorCommand;

CRhinoCommand::result CCommandAddPtAttractor::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	  CRhinoGetNumber gn;
	  gn.SetDefaultNumber( 1.0 ) ;
	  gn.AcceptNothing();
	  gn.GetNumber();
	  double rc = gn.CommandResult();

	  theVoronoiCommand.mySet.AddPointAttractor(context, gn.Number());

	return CRhinoCommand::success;
}

//
// END AddPtAttractor command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN DelPtAttractor command
//

class CCommandDelPtAttractor : public CRhinoCommand
{
public:
	CCommandDelPtAttractor() {}
	~CCommandDelPtAttractor() {}
	UUID CommandUUID()
	{
		// {4EDD85D0-D2E1-41B2-B09B-29B18206FE11}
		static const GUID DelPtAttractorCommand_UUID =
		{ 0x4EDD85D0, 0xD2E1, 0x41B2, { 0xB0, 0x9B, 0x29, 0xB1, 0x82, 0x06, 0xFE, 0x11 } };
		return DelPtAttractorCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"DelPtAttractor"; }
	const wchar_t* LocalCommandName() { return L"DelPtAttractor"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandDelPtAttractor object
static class CCommandDelPtAttractor theDelPtAttractorCommand;

CRhinoCommand::result CCommandDelPtAttractor::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    theVoronoiCommand.mySet.DeletePointAttractor(context);

	return CRhinoCommand::success;
}

//
// END DelPtAttractor command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN AddCurveAttractor command
//

class CCommandAddCurveAttractor : public CRhinoCommand
{
public:
	CCommandAddCurveAttractor() {}
	~CCommandAddCurveAttractor() {}
	UUID CommandUUID()
	{
		// {8312D0D1-31FA-4DF8-BA0F-8FCEED8AA0D8}
		static const GUID AddCurveAttractorCommand_UUID =
		{ 0x8312D0D1, 0x31FA, 0x4DF8, { 0xBA, 0x0F, 0x8F, 0xCE, 0xED, 0x8A, 0xA0, 0xD8 } };
		return AddCurveAttractorCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"AddCurveAttractor"; }
	const wchar_t* LocalCommandName() { return L"AddCurveAttractor"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandAddCurveAttractor object
static class CCommandAddCurveAttractor theAddCurveAttractorCommand;

CRhinoCommand::result CCommandAddCurveAttractor::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	  CRhinoGetNumber gn;
	  gn.SetDefaultNumber( 1.0 ) ;
	  gn.AcceptNothing();
	  gn.GetNumber();
	  double rc = gn.CommandResult();

	  theVoronoiCommand.mySet.AddCurveAttractor(context, gn.Number());

	return CRhinoCommand::success;
}

//
// END AddCurveAttractor command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ClearAll command
//

class CCommandClearAll : public CRhinoCommand
{
public:
	CCommandClearAll() {}
	~CCommandClearAll() {}
	UUID CommandUUID()
	{
		// {152EAA63-2BDC-4B58-8B25-AD4C615F5644}
		static const GUID ClearAllCommand_UUID =
		{ 0x152EAA63, 0x2BDC, 0x4B58, { 0x8B, 0x25, 0xAD, 0x4C, 0x61, 0x5F, 0x56, 0x44 } };
		return ClearAllCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"ClearAll"; }
	const wchar_t* LocalCommandName() { return L"ClearAll"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandClearAll object
static class CCommandClearAll theClearAllCommand;

CRhinoCommand::result CCommandClearAll::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theVoronoiCommand.mySet.ClearAll(context);
	return CRhinoCommand::success;
}

//
// END ClearAll command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ViewEdit command
//

class CCommandViewEdit : public CRhinoCommand
{
public:
	CCommandViewEdit() {}
	~CCommandViewEdit() {}
	UUID CommandUUID()
	{
		// {667D2C97-63BB-4889-A00A-5CFEC7D84778}
		static const GUID ViewEditCommand_UUID =
		{ 0x667D2C97, 0x63BB, 0x4889, { 0xA0, 0x0A, 0x5C, 0xFE, 0xC7, 0xD8, 0x47, 0x78 } };
		return ViewEditCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"ViewEdit"; }
	const wchar_t* LocalCommandName() { return L"ViewEdit"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandViewEdit object
static class CCommandViewEdit theViewEditCommand;

CRhinoCommand::result CCommandViewEdit::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theVoronoiCommand.mySet.ViewEdit(context);
	return CRhinoCommand::success;
}

//
// END ViewEdit command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN RunVoronoi command
//

class CCommandRunVoronoi : public CRhinoCommand
{
public:
	CCommandRunVoronoi() {}
	~CCommandRunVoronoi() {}
	UUID CommandUUID()
	{
		// {FC648232-1B09-49E2-B670-D926CED020D0}
		static const GUID RunVoronoiCommand_UUID =
		{ 0xFC648232, 0x1B09, 0x49E2, { 0xB6, 0x70, 0xD9, 0x26, 0xCE, 0xD0, 0x20, 0xD0 } };
		return RunVoronoiCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"RunVoronoi"; }
	const wchar_t* LocalCommandName() { return L"RunVoronoi"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandRunVoronoi object
static class CCommandRunVoronoi theRunVoronoiCommand;

CRhinoCommand::result CCommandRunVoronoi::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
  CRhinoGetNumber gn1, gn2, gn3;

  gn1.SetDefaultNumber( 0 ) ;
  gn1.AcceptNothing();
  gn1.GetNumber();
  int rc1 = gn1.CommandResult();
	
  float arg1 = (float)gn1.Number();

  gn2.SetDefaultNumber( 0 ) ;
  gn2.AcceptNothing();
  gn2.GetNumber();
  int rc2 = gn2.CommandResult();
	
  float arg2 = (float)gn2.Number();

  gn3.SetDefaultNumber( 0 ) ;
  gn3.AcceptNothing();
  gn3.GetNumber();
  int rc3 = gn3.CommandResult();
	
  bool arg3 = (bool)gn3.Number();

  theVoronoiCommand.mySet.RunVoronoi(context, arg3, arg1, arg2);
  return CRhinoCommand::success;
}

//
// END RunVoronoi command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TogglePtHide command
//

class CCommandTogglePtHide : public CRhinoCommand
{
public:
	CCommandTogglePtHide() {}
	~CCommandTogglePtHide() {}
	UUID CommandUUID()
	{
		// {88E8DF07-2DBC-4AE8-8A13-356DB628F6E5}
		static const GUID TogglePtHideCommand_UUID =
		{ 0x88E8DF07, 0x2DBC, 0x4AE8, { 0x8A, 0x13, 0x35, 0x6D, 0xB6, 0x28, 0xF6, 0xE5 } };
		return TogglePtHideCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TogglePtHide"; }
	const wchar_t* LocalCommandName() { return L"TogglePtHide"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTogglePtHide object
static class CCommandTogglePtHide theTogglePtHideCommand;

CRhinoCommand::result CCommandTogglePtHide::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	  CRhinoGetNumber gn3;
	  gn3.SetDefaultNumber( 0 ) ;
	  gn3.AcceptNothing();
	  gn3.GetNumber();
	  int rc3 = gn3.CommandResult();
		
	  bool arg3 = (bool)gn3.Number();

	theVoronoiCommand.mySet.ToggleHidePoints(context, arg3);
	return CRhinoCommand::success;
}

//
// END TogglePtHide command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN UndoCurves command
//

class CCommandUndoCurves : public CRhinoCommand
{
public:
	CCommandUndoCurves() {}
	~CCommandUndoCurves() {}
	UUID CommandUUID()
	{
		// {B9E715ED-94AE-4343-AFC9-71CDD523B888}
		static const GUID UndoCurvesCommand_UUID =
		{ 0xB9E715ED, 0x94AE, 0x4343, { 0xAF, 0xC9, 0x71, 0xCD, 0xD5, 0x23, 0xB8, 0x88 } };
		return UndoCurvesCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"UndoCurves"; }
	const wchar_t* LocalCommandName() { return L"UndoCurves"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandUndoCurves object
static class CCommandUndoCurves theUndoCurvesCommand;

CRhinoCommand::result CCommandUndoCurves::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theVoronoiCommand.mySet.UndoCurves(context);
	return CRhinoCommand::success;
}

//
// END UndoCurves command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN UndoPoints command
//

class CCommandUndoPoints : public CRhinoCommand
{
public:
	CCommandUndoPoints() {}
	~CCommandUndoPoints() {}
	UUID CommandUUID()
	{
		// {D7EBE0AC-59A2-4DFA-BFB5-0B9C207CFD8E}
		static const GUID UndoPointsCommand_UUID =
		{ 0xD7EBE0AC, 0x59A2, 0x4DFA, { 0xBF, 0xB5, 0x0B, 0x9C, 0x20, 0x7C, 0xFD, 0x8E } };
		return UndoPointsCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"UndoPoints"; }
	const wchar_t* LocalCommandName() { return L"UndoPoints"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandUndoPoints object
static class CCommandUndoPoints theUndoPointsCommand;

CRhinoCommand::result CCommandUndoPoints::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theVoronoiCommand.mySet.UndoPoints(context);
	return CRhinoCommand::success;
}

//
// END UndoPoints command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN BurnData command
//

class CCommandBurnData : public CRhinoCommand
{
public:
	CCommandBurnData() {}
	~CCommandBurnData() {}
	UUID CommandUUID()
	{
		// {41DFD99A-40F0-45B7-A66D-4A713289F598}
		static const GUID BurnDataCommand_UUID =
		{ 0x41DFD99A, 0x40F0, 0x45B7, { 0xA6, 0x6D, 0x4A, 0x71, 0x32, 0x89, 0xF5, 0x98 } };
		return BurnDataCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"BurnData"; }
	const wchar_t* LocalCommandName() { return L"BurnData"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandBurnData object
static class CCommandBurnData theBurnDataCommand;

CRhinoCommand::result CCommandBurnData::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theVoronoiCommand.mySet.BurnData(context);
	return CRhinoCommand::success;
}

//
// END BurnData command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TrimBrep command
//

class CCommandTrimBrep : public CRhinoCommand
{
public:
	CCommandTrimBrep() {}
	~CCommandTrimBrep() {}
	UUID CommandUUID()
	{
		// {E14CFA4E-4DC4-418B-9E99-0B753094F40B}
		static const GUID TrimBrepCommand_UUID =
		{ 0xE14CFA4E, 0x4DC4, 0x418B, { 0x9E, 0x99, 0x0B, 0x75, 0x30, 0x94, 0xF4, 0x0B } };
		return TrimBrepCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"TrimBrep"; }
	const wchar_t* LocalCommandName() { return L"TrimBrep"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandTrimBrep object
static class CCommandTrimBrep theTrimBrepCommand;

CRhinoCommand::result CCommandTrimBrep::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theVoronoiCommand.mySet.TrimBrep(context);
	return CRhinoCommand::success;
}

//
// END TrimBrep command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN UndoTrim command
//

class CCommandUndoTrim : public CRhinoCommand
{
public:
	CCommandUndoTrim() {}
	~CCommandUndoTrim() {}
	UUID CommandUUID()
	{
		// {33ED487-AC73-41F7-B658-CD030BA8F811}
		static const GUID UndoTrimCommand_UUID =
		{ 0x33ED487, 0xAC73, 0x41F7, { 0xB6, 0x58, 0xCD, 0x03, 0x0B, 0xA8, 0xF8, 0x11 } };
		return UndoTrimCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"UndoTrim"; }
	const wchar_t* LocalCommandName() { return L"UndoTrim"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandUndoTrim object
static class CCommandUndoTrim theUndoTrimCommand;

CRhinoCommand::result CCommandUndoTrim::RunCommand( const CRhinoCommandContext& context )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theVoronoiCommand.mySet.UndoTrim(context);
	return CRhinoCommand::success;
}

//
// END UndoTrim command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
