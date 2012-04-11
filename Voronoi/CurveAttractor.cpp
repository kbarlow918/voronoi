#include "StdAfx.h"
#include "CurveAttractor.h"
#include "PointAttractor.h"

CurveAttractor::CurveAttractor(void)
{
}

CurveAttractor::CurveAttractor(double aStrength, const ON_Surface* aSurface, CRhinoObjRef aObjRef)
{
	strength = aStrength;
	surface = aSurface;
	objRef = aObjRef;
	curveObj = objRef.Curve();
}

CurveAttractor::~CurveAttractor(void)
{
}

double CurveAttractor::GetScore(double u, double v, ON_3dPoint aPoint)
{
	PointAttractor pa;
	GetClosestPointAttractor(aPoint, &pa);
	if(&pa != NULL)
		return pa.GetScore(u, v);

	RhinoApp().Print("\nError during curve attractor score evaluation");
	return 0.0;
}

void CurveAttractor::GetClosestPointAttractor(ON_3dPoint aPoint, PointAttractor *pa)
{
	ON_3dPoint closestPoint, surfacePointTemp, surfacePointFinal;
	double closestPointParam, attractorU, attractorV;

	//get the 3d point on the surface
	//surfacePointTemp = surface->PointAt(u, v);
	surfacePointTemp = aPoint;
	RhinoApp().Print(" surface point: %f %f %f ", surfacePointTemp.x, surfacePointTemp.y, surfacePointTemp.z);

	//find parameter of closest point to that point on the curve
	if(objRef.Curve()->GetClosestPoint(surfacePointTemp, &closestPointParam))
	{
		RhinoApp().Print(" point on curve param: %f ", closestPointParam);

		//get the actual point
		closestPoint = objRef.Curve()->PointAt(closestPointParam);		
		RhinoApp().Print(" point on curve: %f %f %f \n", closestPoint.x, closestPoint.y, closestPoint.z);

		//use that to get parameters of closest point on the surface (just in case)
		if(surface->GetClosestPoint(closestPoint, &attractorU, &attractorV))
		{
			//get the actual point
			surfacePointFinal = surface->PointAt(attractorU, attractorV);
			
			//make a temporary point attractor there
			*pa = (PointAttractor(surfacePointFinal, strength, NULL, surface));		
		}
	}
	pa = NULL;
}

void CurveAttractor::SetObjRef(CRhinoObjRef aObjRef)
{
	objRef = aObjRef;
	curveObj = objRef.Curve();
}
const ON_Curve* CurveAttractor::GetCurve(void)
{
	return curveObj;
}
CRhinoObjRef CurveAttractor::GetObjRef(void)
{
	return objRef;
}