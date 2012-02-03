#include "StdAfx.h"
#include "RndPointSet.h"

RndPointSet::RndPointSet(void)
{
}

RndPointSet::~RndPointSet(void)
{
}

void RndPointSet::DrawPoints( const CRhinoCommandContext& context, int numPoints )
{
  double x = 0.0, y = 0.0;
  ON_wString sx, sy, sz;
 
  // Pick a brep to evaluate
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select surface or polysurface to evaluate" );
  go.SetGeometryFilter( CRhinoGetObject::surface_object|CRhinoGetObject::polysrf_object );
  go.GetObjects( 1, 1 );
  //if( go.CommandResult() != success )
  //  return go.CommandResult();
 
  // Get the brep geometry
  const CRhinoObjRef& ref = go.Object(0);
  const ON_Brep* brep = ref.Brep();
  //if( !brep )
  //  return failure;
 
  const ON_BoundingBox bbox = brep->BoundingBox();
  
  int i;
  for(i = 0; i < numPoints; i++)
  {
	  ON_3dPoint p0( fRand(bbox.m_min.x, bbox.m_max.x), fRand(bbox.m_min.y, bbox.m_max.y), fRand(bbox.m_min.z, bbox.m_max.z) );
	  context.m_doc.AddPointObject(p0);
  }
  context.m_doc.Redraw();
 //this is drawing things outside the bounding box for some reason
}

double RndPointSet::fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}