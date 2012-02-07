#pragma once

class RndPointSet
{
public:
	RndPointSet(void);
	~RndPointSet(void);
	void DrawPoints( const CRhinoCommandContext& context, int numPoints );
	void Test( const CRhinoCommandContext& context, double a, double b, double c, double d );
	double fRand(double fMin, double fMax);
};
