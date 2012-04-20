#include "StdAfx.h"
#include "PointAttractor.h"
#include "RndPointSet.h"
#include <cmath>

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
	myU = 0.0;
	myV = 0.0;
	surface->GetDomain(0, &u1, &u2);
	surface->GetDomain(1, &v1, &v2);
	surface->GetClosestPoint(point, &myU, &myV);
}

void PointAttractor::Shift(double u, double v, double* uSum, double* vSum, double overallStrength)
{
	double uDiff = myU-u;
	double vDiff = myV-v;

	if(strength < 0) //reverse vector and make sure it isn't too close to the edge
	{
		uDiff *= -1;
		vDiff *= -1;

		if(uDiff < 0 && u1 - u > uDiff) //going left and closer to edge than attractor
		{
			vDiff *= abs((u1-u)/uDiff); //scale down vDiff to match
			uDiff = u1 - u; //has to be negative
		}
		else if(u2 - u < uDiff) //going right and closer to edge than attractor
		{
			vDiff *= abs((u2-u)/uDiff); //scale down vDiff to match
			uDiff = u2 - u;
		}

		//by symmetry:
		if(vDiff < 0 && v1 - v > vDiff)
		{
			uDiff *= abs((v1-v)/vDiff);
			vDiff = v1 - v;
		}
		else if(v2 - v < vDiff)
		{
			uDiff *= abs((v2-v)/vDiff);
			vDiff = v2 - v;
		}

		//now we want to increase the potential push distance if there is room to do so
		double uStep = uDiff;
		double vStep = vDiff;

		while(	uDiff + uStep > u1 &&
				uDiff + uStep < u2 &&
				vDiff + vStep > v1 &&
				vDiff + vStep < v2)
		{
			uDiff += uStep;
			vDiff += vStep;
		}
	}

	double scaleFactor = RndPointSet::fRand(abs(strength)*(overallStrength/100), abs(strength))/MAX_STRENGTH;

	*uSum += (scaleFactor*uDiff);
	*vSum += (scaleFactor*vDiff);

	//RhinoApp().Print("pt: %f  %f   me: %f  %f   diff: %f  %f   scale:  %f   sums: %f   %f", u, v, myU, myV, uDiff, vDiff, scaleFactor, *uSum, *vSum);
}

bool PointAttractor::CheckSurface(const ON_Surface* aSurface)
{
	return aSurface == surface;
}
