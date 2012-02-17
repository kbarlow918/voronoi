#pragma once

class PointAttractor
{
public:
	PointAttractor(void);
	~PointAttractor(void);
	PointAttractor(ON_3dPoint aPoint, double aStrength, CRhinoPointObject* aPointObj, const ON_Surface* aSurface);
	double GetScore(double u, double v);

	CRhinoPointObject* pointObj;


private:
	ON_3dPoint point;
	double strength;
	const ON_Surface* surface;
	double maxDist;

	void SetMaxDist();
};
