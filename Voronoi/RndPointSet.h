#pragma once

class RndPointSet
{
public:
	RndPointSet(void);
	~RndPointSet(void);
	void DrawPoints( const CRhinoCommandContext& context, int numPoints );
	double fRand(double fMin, double fMax);
};
