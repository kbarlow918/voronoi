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
  go.SetCommandPrompt( L"Select surface to evaluate " );
  go.SetGeometryFilter( CRhinoGetObject::surface_object);
  go.GetObjects( 1, 1 );
 
  // Get the surface geometry
  const CRhinoObjRef& ref = go.Object(0);

  if(ref == NULL)
  {
	RhinoApp().Print(L"reference initialization error");
	return ;
  }

  const ON_Surface* obj = ref.Surface();

  if(obj == NULL)
  {
	RhinoApp().Print(L"object initialization error");
	return ;
  }
	
  double u1, u2, v1, v2;

  if(obj->GetDomain(0, &u1, &u2) && obj->GetDomain(1, &v1, &v2))
  {
	  int i;
	  for(i = 0; i < numPoints; i++)
	  {
		  ON_3dPoint p0 = obj->PointAt( fRand(u1, u2), fRand(v1, v2));
		  //context.m_doc.AddPointObject(p0); 
		  //RhinoApp().Print(L"p0.x = %f\n",p0.x);
		  //RhinoApp().Print(L"p0.y = %f\n",p0.y);
		  //RhinoApp().Print(L"p0.z = %f\n",p0.z);
		  double u, v = 0.0;						//the following might be redundant
		  obj->GetClosestPoint(p0, &u, &v);			
		  //RhinoApp().Print(L"p0.u = %f\n",u);
		  //RhinoApp().Print(L"p0.v = %f\n",v);
		  ON_3dPoint p1 = obj->PointAt( u, v);
		  
		  context.m_doc.AddPointObject(p1);
	  }
	  context.m_doc.Redraw();
  }
  else
  {
	RhinoApp().Print(L"object domain error");
	return ;
  }

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