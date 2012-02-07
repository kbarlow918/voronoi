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
 
  // Pick a surface to evaluate
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select surface to evaluate - test" );
  go.SetGeometryFilter( CRhinoGetObject::surface_object);
  go.GetObjects( 1, 1 );

 
  // Get the surface geometry
  const CRhinoObjRef& ref = go.Object(0);
  const ON_Surface* obj = ref.Surface();

  double u1, u2, v1, v2;
  
  if(obj->GetDomain(0, &u1, &u2) && obj->GetDomain(0, &v1, &v2))
  {
	  int i;
	  for(i = 0; i < numPoints; i++)
	  {
		  ON_3dPoint p0 = obj->PointAt( fRand(u1, u2), fRand(v1, v2));
		  double u, v;
		  obj->GetClosestPoint(p0, &u, &v);
		  ON_3dPoint p1 = obj->PointAt( u, v);

		  context.m_doc.AddPointObject(p1);
	  }
	  context.m_doc.Redraw();
  }

 //this is drawing things outside the bounding box for some reason
}

void RndPointSet::Test( const CRhinoCommandContext& context, double a, double b, double c, double d )
{
  // Pick a surface to evaluate
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select surface to evaluate - test function" );
  go.SetGeometryFilter( CRhinoGetObject::surface_object);
  go.GetObjects( 1, 1 );

 
  // Get the surface geometry
  const CRhinoObjRef& ref = go.Object(0);
  const ON_Surface* obj = ref.Surface();

  ON_3dPoint p0 = obj->PointAt( a, b);
  double u, v;
  obj->GetClosestPoint(p0, &u, &v);
  ON_3dPoint p1 = obj->PointAt( u, v);

  context.m_doc.AddPointObject(p1);
  context.m_doc.Redraw();
}

double RndPointSet::fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}