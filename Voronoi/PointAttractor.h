#pragma once

class PointAttractor
{
public:
	PointAttractor(void);
	~PointAttractor(void);
	PointAttractor(ON_3dPoint aPoint, double aStrength, CRhinoPointObject* aPointObj, const ON_Surface* aSurface);
	void Shift(double u, double v, double* uSum, double* vSum, double overallStrength);
	bool CheckSurface(const ON_Surface* aSurface);

	CRhinoPointObject* pointObj;
	double strength;
	ON_3dPoint point;

private:
	const ON_Surface* surface;
	double maxDist;
	double myU, myV;
	double u1, u2, v1, v2;
	static const int MAX_STRENGTH = 100;
};
