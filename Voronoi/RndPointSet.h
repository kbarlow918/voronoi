#pragma once
#include <vector>
#include "PointAttractor.h"

class RndPointSet
{
public:
	RndPointSet(void);
	~RndPointSet(void);
	void AddPointAttractor( const CRhinoCommandContext& context, double value );
	void DrawPoints( const CRhinoCommandContext& context, int numPoints );
	void Test( const CRhinoCommandContext& context, double a, double b, double c, double d );
	double fRand(double fMin, double fMax);
	bool ProjectCurveToBrep(
        const ON_Brep& brep, 
        const ON_Curve& curve, 
        const ON_3dVector& dir, 
        double tolerance,
        ON_SimpleArray<ON_Curve*>& output_curves
        );

private:
	std::vector<PointAttractor> pointAttractors;
};
