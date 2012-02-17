#include "StdAfx.h"
#include "PointAttractor.h"

PointAttractor::PointAttractor(void)
{
}

PointAttractor::~PointAttractor(void)
{
}


PointAttractor::PointAttractor(ON_3dPoint aPoint, double aStrength, CRhinoPointObject* aPointObj, const ON_Surface* aSurface)
{
	point = aPoint;
	strength = aStrength;
	pointObj = aPointObj;
	surface = aSurface;
	maxDist = 0.0;
}

void PointAttractor::SetMaxDist()
{
	double u1, u2, v1, v2;
	double myU, myV;
	if(surface->GetDomain(0, &u1, &u2) && surface->GetDomain(1, &v1, &v2))
	{
		RhinoApp().Print("Domain U: %f  %f   V: %f  %f", u1, u2, v1, v2);
		if(surface->GetClosestPoint(pointObj->Point(), &myU, &myV))
		{
			RhinoApp().Print("\nGot UV: %f %f", myU, myV);
		}
	}
}

double PointAttractor::GetScore(double u, double v)
{
	if(maxDist == 0.0)
		SetMaxDist();

	return 0.0;
}