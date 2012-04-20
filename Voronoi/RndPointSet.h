#pragma once
#include <vector>
#include "PointAttractor.h"
#include "CurveAttractor.h"
#include "CellBorder.h"

class RndPointSet
{
public:
	RndPointSet(void);
	~RndPointSet(void);
	void RunVoronoi(const CRhinoCommandContext& context, bool drawCellLines);
	void AddPointAttractor( const CRhinoCommandContext& context, double value );
	void AddCurveAttractor( const CRhinoCommandContext& context, double value );
	void BurnData(const CRhinoCommandContext& context);
	void DeletePointAttractor( const CRhinoCommandContext& context );
	void TrimBrep( const CRhinoCommandContext& context );
	bool EvaluateAttractorsManyVectors(const CRhinoCommandContext& context, unsigned int numPoints, double overallStrength);
	void ViewEdit( const CRhinoCommandContext& context );
	void DrawPoints( const CRhinoCommandContext& context, unsigned int numPoints, double overallStrength );
	void ClearAll(const CRhinoCommandContext& context);
	void UndoCurves(const CRhinoCommandContext& context);
	void UndoPoints(const CRhinoCommandContext& context);
	void ToggleHidePoints(const CRhinoCommandContext& context, bool drawCellLines);
	static double fRand(double fMin, double fMax);
	
private:
	std::vector<PointAttractor> pointAttractors;
	std::vector<CRhinoPointObject*> points;
	std::vector<CurveAttractor> curveAttractors;
	std::vector<CRhinoCurveObject*> surfaceCurves;
	std::vector<CRhinoCurveObject*> cellLines;
	std::vector<CellBorder> cellBorderList;
	ON_SimpleArray<const ON_Curve*> curveArr;
	bool pointsHidden;
	const ON_Surface* surface;
	const ON_Brep* mainBrep;
};

int sortPoints(const ON_2dPoint* p1, const ON_2dPoint* p2);
