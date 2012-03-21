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
	CVoronoiDialog *m_dialog = new CVoronoiDialog( CWnd::FromHandle(RhinoApp().MainWnd()) );
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
	theVoronoiCommand.mySet.ViewEdit(context);
	return CRhinoCommand::success;
}

//
// END ViewEdit command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
