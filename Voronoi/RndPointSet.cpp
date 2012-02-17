#include "StdAfx.h"
#include "RndPointSet.h"

RndPointSet::RndPointSet(void)
{
	srand(time(NULL));
}

RndPointSet::~RndPointSet(void)
{
	
}

void RndPointSet::AddPointAttractor( const CRhinoCommandContext& context, double value )
{
  // Pick a surface to evaluate
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select surface where attractor will be added" );
  go.SetGeometryFilter( CRhinoGetObject::surface_object);
  go.GetObjects( 1, 1 );
 
  // Get the surface geometry
  const ON_Surface* ref = go.Object(0).Surface();

  if(ref == NULL)
  {
	RhinoApp().Print(L"reference initialization error");
	return ;
  }

  CRhinoGetPoint getPoint;
  getPoint.SetCommandPrompt( L"Select point on the surface" );
  getPoint.Constrain( *ref ); //force point to be on surface
  if(getPoint.GetPoint( ) == CRhinoGet::point) //did it work?
  {
	  ON_3dPoint attractor = getPoint.Point();

	  //draw the point and add it to the attractors list
	  PointAttractor pa(attractor, value, context.m_doc.AddPointObject(attractor), ref);
	  pointAttractors.push_back(pa);
	  context.m_doc.Redraw();
  }
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
	
  double u1, u2, v1, v2, minStrength;

  if(pointAttractors.size() > 0)
  {
	  //find the attractor with the least strength (magnitude)
	  int j;
	  minStrength = abs(pointAttractors.at(0).strength);
	  for(j = 1; j < pointAttractors.size(); j++)
	  {
		  if(abs(pointAttractors.at(j).strength) < minStrength)
			  minStrength = abs(pointAttractors.at(j).strength);
	  }
	  RhinoApp().Print("\nMin Strength Attractor: %f", minStrength);
  }

  if(obj->GetDomain(0, &u1, &u2) && obj->GetDomain(1, &v1, &v2))
  {
	  //RhinoApp().Print("Domain U: %f  %f   V: %f  %f", u1, u2, v1, v2);
	  int i;
	  ON_3dPoint prev;
	  for(i = 0; i < numPoints; i++)
	  {
		  bool redo = true; //used to redo due to attractors
		  ON_3dPoint p1;
		  while(redo)
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
			  p1 = obj->PointAt( u, v);
			  //code to make lines between points
			  /*if(i>0)
			  {
				  ON_LineCurve l0 = ON_LineCurve(p1, prev);
				  ON_3dVector v0 = ON_3dVector(0,0,1);
				  ON_SimpleArray<ON_Curve*> arr;
				  ProjectCurveToBrep(*obj->BrepForm(), l0, v0, 1.0, arr);
				  if(arr.First() == NULL)
				  {
					RhinoApp().Print(L"no projection");
				  }else
				  {
					context.m_doc.AddCurveObject(**arr.First());
				  }
				  
			  }
			  prev = p1;*/

			  //deal with attractors
			  if(pointAttractors.size() > 0)
			  {
				  double totalScore = 0.0;
				  double totalMultOfMinStrength = 0.0;
				  int j;
				  for(j = 0; j < pointAttractors.size(); j++)
				  {
					  double score = pointAttractors.at(j).GetScore(u,v);
					  //How many times stronger than the weakest is this attractor?
					  double minStrengthMult = abs(pointAttractors.at(j).strength)/minStrength;
					  RhinoApp().Print("\nPoint %f %f Attractor %d Score %f Mult %f", u, v, j, score, minStrengthMult);
					  totalScore += score * minStrengthMult; //we want to give stronger attractors a bigger "vote"
					  totalMultOfMinStrength += minStrengthMult;
				  }

				  double stayChance = totalScore/totalMultOfMinStrength;
				  double rolled = fRand(0, 1);
				  RhinoApp().Print("\nChance to stay: %f Rolled: %f", stayChance, rolled);
				  if(rolled > stayChance)
				  {
					  RhinoApp().Print("\nRepicking point");
				  }
				  else
				  {
					  RhinoApp().Print("\nPoint accepted");
					  redo = false;
				  }
			  }
			  else
			  {
				  redo = false;
			  }
		  }
		  context.m_doc.AddPointObject(p1);
	  }

	  for(i = 0; i < pointAttractors.size(); i++)
	  {
		  context.m_doc.DeleteObject(pointAttractors.at(i).pointObj);
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

/*
Description:
  Projects a curve onto a surface or polysurface
Parameters:
  brep  - [in] The brep to project the curve onto.
  curve - [in] The curve to project.
  dir   - [in] The direction of the projection.
  tol   - [in] The intersection tolerance.
  output_curves - [out] The output curves. 
                        NOTE, the caller is responsible 
                        for destroying these curves.
Returns:
  true if successful.
  false if unsuccessful.
*/
bool RndPointSet::ProjectCurveToBrep(
        const ON_Brep& brep, 
        const ON_Curve& curve, 
        const ON_3dVector& dir, 
        double tolerance,
        ON_SimpleArray<ON_Curve*>& output_curves
        )
{
  ON_3dVector n = dir;
  if( !n.Unitize() ) 
    return false;
 
  ON_BoundingBox bbox = brep.BoundingBox();
  bbox.Union( curve.BoundingBox() );
 
  ON_Surface* pExtrusion = RhinoExtrudeCurveStraight( &curve, dir, bbox.Diagonal().Length() );
  if( 0 == pExtrusion )
    return false;
 
  ON_Brep* pBrep = ON_Brep::New();
  pBrep->Create( pExtrusion );
 
  BOOL rc = RhinoIntersectBreps( *pBrep, brep, tolerance, output_curves );
  delete pBrep; // Don't leak...
 
  return ( rc ) ? true : false;
}