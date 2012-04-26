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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

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


void CurveAttractor::GetClosestPointAttractor(ON_3dPoint aPoint, PointAttractor *pa)
{
	ON_3dPoint closestPoint, surfacePointTemp, surfacePointFinal;
	double closestPointParam, attractorU, attractorV;

	//get the 3d point on the surface
	//surfacePointTemp = surface->PointAt(u, v);
	surfacePointTemp = aPoint;
	//RhinoApp().Print(" surface point: %f %f %f ", surfacePointTemp.x, surfacePointTemp.y, surfacePointTemp.z);

	//find parameter of closest point to that point on the curve
	if(objRef.Curve()->GetClosestPoint(surfacePointTemp, &closestPointParam))
	{
		//RhinoApp().Print(" point on curve param: %f ", closestPointParam);

		//get the actual point
		closestPoint = objRef.Curve()->PointAt(closestPointParam);		
		//RhinoApp().Print(" point on curve: %f %f %f \n", closestPoint.x, closestPoint.y, closestPoint.z);

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
bool CurveAttractor::CheckSurface(const ON_Surface* aSurface)
{
	return aSurface == surface;
}