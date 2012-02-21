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
	
  theVoronoiCommand.mySet.DrawPoints(context, (int) gn.Number());

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
		
	  RndPointSet mySet;
	  theVoronoiCommand.mySet.AddPointAttractor(context, gn.Number());

	return CRhinoCommand::success;
}

//
// END AddPtAttractor command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////