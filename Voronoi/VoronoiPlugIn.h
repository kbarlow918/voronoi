/////////////////////////////////////////////////////////////////////////////
// VoronoiPlugIn.h : main header file for the Voronoi plug-in
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CVoronoiPlugIn
// See VoronoiPlugIn.cpp for the implementation of this class
//

class CVoronoiPlugIn : public CRhinoUtilityPlugIn
{
public:
  CVoronoiPlugIn();
  ~CVoronoiPlugIn();

  // Required overrides
  const wchar_t* PlugInName() const;
  const wchar_t* PlugInVersion() const;
  GUID PlugInID() const;
  BOOL OnLoadPlugIn();
  void OnUnloadPlugIn();

  // Online help overrides
  BOOL AddToPlugInHelpMenu() const;
  BOOL OnDisplayPlugInHelp( HWND hWnd ) const;

private:
  ON_wString m_plugin_version;

  // TODO: Add additional class information here
};

CVoronoiPlugIn& VoronoiPlugIn();



