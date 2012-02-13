#pragma once
#include <vector>

struct PointAttractor {
	ON_3dPoint point;
	double strength;
	CRhinoPointObject* pointObj;

	PointAttractor(ON_3dPoint aPoint, double aStrength, CRhinoPointObject* aPointObj)
	{
		point = aPoint;
		strength = aStrength;
		pointObj = aPointObj;
	}
};

class RndPointSet
{
public:
	RndPointSet(void);
	~RndPointSet(void);
	void AddPointAttractor( const CRhinoCommandContext& context, double value );
	void DrawPoints( const CRhinoCommandContext& context, int numPoints );
	void Test( const CRhinoCommandContext& context, double a, double b, double c, double d );
	double fRand(double fMin, double fMax);

private:
	std::vector<PointAttractor> pointAttractors;
};
