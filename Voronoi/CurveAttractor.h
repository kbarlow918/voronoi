#pragma once
#include "PointAttractor.h"

class CurveAttractor
{
public:
	CurveAttractor(void);
	~CurveAttractor(void);
	CurveAttractor(double aStrength, const ON_Surface* aSurface, CRhinoObjRef aObjRef);
	void GetClosestPointAttractor(ON_3dPoint aPoint, PointAttractor* pa);
	void SetObjRef(CRhinoObjRef aObjRef);
	CRhinoObjRef GetObjRef(void);
	const ON_Curve* GetCurve(void);

	double strength;

private:	
	const ON_Surface* surface;
	const ON_Curve* curveObj;
	CRhinoObjRef objRef;
};
