#pragma once

class CurveAttractor
{
public:
	CurveAttractor(void);
	~CurveAttractor(void);
	CurveAttractor(const ON_Curve* aCurve, double aStrength, const ON_Surface* aSurface);
	double GetScore(double u, double v, ON_3dPoint aPoint);

	const ON_Curve* curveObj;
	double strength;

private:	
	const ON_Surface* surface;

};
