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
	SetMaxDist();
}

void PointAttractor::SetMaxDist()
{
	if(surface->GetDomain(0, &u1, &u2) && surface->GetDomain(1, &v1, &v2))
	{
		//RhinoApp().Print("Domain U: %f  %f   V: %f  %f", u1, u2, v1, v2);

		//Get the UV representation of the chosen attractor
		if(surface->GetClosestPoint(point, &myU, &myV))
		{
			RhinoApp().Print("\nGot PA UV: %f %f", myU, myV);

			//Divide the UV plane into quadrants
			double uMid, vMid;
			uMid = abs(u1-u2) + u1;
			vMid = abs(v1-v2) + v1;

			/* The largest possible distance on the UV plane will always be from
			the given point to the corner of the opposite quadrant - we need to
			figure out which quadrant our point is in so we can find the corner of
			the opposite quadrant */
			double cornerU, cornerV;

			if(myU <= uMid)
			{
				cornerU = u2;
			}
			else
			{
				cornerU = u1;
			}
			if(myV <= vMid)
			{
				cornerV = v2;
			}
			else
			{
				cornerV = v1;
			}

			//We won't take the square root because it doesn't matter for ratios
			maxDist = pow(myU-cornerU, 2) + pow(myV-cornerV, 2);
			//RhinoApp().Print("\nCorner: %f %f", cornerU, cornerV);
			//RhinoApp().Print("\nMax Dist Set: %f", maxDist);
		}
	}
	else
	{
		RhinoApp().Print("\nError while getting domain");
	}
}

double PointAttractor::GetScore(double u, double v)
{
	//Score from 0 to 1 based on percentage of max distance
	double score = ((pow(myU-u, 2) + pow(myV-v, 2))/maxDist);

	//Above method gives high score to far points, need to flip
	//if the attractor is positive (close is good)
	if(strength > 0)
		score = 1-score;
	
	//Weight the score based on the specificed strength
	return abs(score/strength);
}
void PointAttractor::Shift(double u, double v, double* uSum, double* vSum)
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

	double scaleFactor = RndPointSet::fRand(0, abs(strength))/MAX_STRENGTH;
	//double scaleFactor = strength/MAX_STRENGTH;

	*uSum += (scaleFactor*uDiff);
	*vSum += (scaleFactor*vDiff);

	RhinoApp().Print("pt: %f  %f   me: %f  %f   diff: %f  %f   scale:  %f   sums: %f   %f", u, v, myU, myV, uDiff, vDiff, scaleFactor, *uSum, *vSum);
}
