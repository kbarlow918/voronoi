/*
Voronoi Diagram Generator for Surfaces in Rhinoceros 3d
Copyright (C) 2012 Kevin Barlow, Stephen Sheafer and Joe Wolter

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "StdAfx.h"
#include "RndPointSet.h"
#include "VoronoiDiagramGenerator.h"

float *xValues;
float *yValues;
int vsize = 0;
float avgU, avgV; //used to calculate center to sort points for trim curves
std::vector<ON_SimpleArray<ON_2dPoint>> rndPoints;

RndPointSet::RndPointSet(void)
{
	srand((unsigned int)time(NULL));
	pointsHidden = true;
	surface = NULL;
	trimmedBrep = NULL;
}

RndPointSet::~RndPointSet(void)
{
	
}

void RndPointSet::AddPointAttractor( const CRhinoCommandContext& context, double value )
{
  // Pick a surface to evaluate
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select surface where attractor will be added" );
  go.SetGeometryFilter( CRhinoGetObject::surface_object);
  go.GetObjects( 1, 1 );
 
  // Get the surface geometry
  const ON_Surface* ref = go.Object(0).Surface();
  
  if(ref == NULL)
  {
	RhinoApp().Print(L"reference initialization error");
	return ;
  }

  CRhinoGetPoint getPoint;
  getPoint.SetCommandPrompt( L"Select point on the surface" );
  getPoint.Constrain( *ref ); //force point to be on surface
  if(getPoint.GetPoint( ) == CRhinoGet::point) //did it work?
  {
	  ON_3dPoint attractor = getPoint.Point();

	  //draw the point and add it to the attractors list
	  PointAttractor pa(attractor, value, context.m_doc.AddPointObject(attractor), ref);
	  pointAttractors.push_back(pa);
	  context.m_doc.Redraw();
  }
}

void RndPointSet::AddCurveAttractor( const CRhinoCommandContext& context, double value )
{
  // Pick a surface to evaluate
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select surface where attractor will be added" );
  go.SetGeometryFilter( CRhinoGetObject::surface_object);
  go.GetObjects( 1, 1 );
 
  // Get the surface geometry
  const ON_Surface* surf = go.Object(0).Surface();

  if(surf == NULL)
  {
	RhinoApp().Print(L"reference initialization error");
	return ;
  }

  go.SetCommandPrompt( L"Select curve" );
  go.SetGeometryFilter( CRhinoGetObject::curve_object);
  go.GetObjects( 1, 1 );

  // Get the curve
  const ON_Curve* ref = go.Object(0).Curve();
  if(ref == NULL)
  {
	RhinoApp().Print(L"reference initialization error");
	return ;
  }
  else
  {
	CurveAttractor ca(value, surf, go.Object(0));
	curveAttractors.push_back(ca);
	context.m_doc.Redraw();
  }
}

void RndPointSet::DeletePointAttractor( const CRhinoCommandContext& context )
{
  CRhinoGetObject getPoint;

  const ON_Point* ptAttractor;
  const ON_Curve* curveAttractor;

  getPoint.SetCommandPrompt( L"Select attractor to delete" );
  getPoint.GetObjects(1,1);
  if((ptAttractor = getPoint.Object(0).Point()) != NULL) //did it work?
  {
	  //RhinoApp().Print("got point\n");
	  //RhinoApp().Print("pt %f %f %f\n", attractor.x, attractor.y, attractor.z);
	  unsigned int j;
	  for(j = 0; j < pointAttractors.size(); j++)
	  {
		  //RhinoApp().Print("attr: %f %f %f\n", pointAttractors.at(j).point.x, pointAttractors.at(j).point.y, pointAttractors.at(j).point.z);
		  if(pointAttractors.at(j).point == ptAttractor->point)
		  {
			  context.m_doc.DeleteObject(pointAttractors.at(j).pointObj);
			  pointAttractors.erase(pointAttractors.begin() + j);
			  context.m_doc.Redraw();
			  RhinoApp().Print("Attractor deleted\n");
			  return;
		  }
	  }	  
  }
  else if((curveAttractor = getPoint.Object(0).Curve()) != NULL) //did it work?
  {
	  //RhinoApp().Print("got curve\n");
	  //RhinoApp().Print("pt %f %f %f\n", attractor.x, attractor.y, attractor.z);
	  unsigned int j;
	  for(j = 0; j < curveAttractors.size(); j++)
	  {
		  //RhinoApp().Print("attr: %f %f %f\n", pointAttractors.at(j).point.x, pointAttractors.at(j).point.y, pointAttractors.at(j).point.z);
		  if(curveAttractors.at(j).GetCurve() == curveAttractor)
		  {
			  context.m_doc.DeleteObject(curveAttractors.at(j).GetObjRef());
			  curveAttractors.erase(curveAttractors.begin() + j);
			  context.m_doc.Redraw();
			  RhinoApp().Print("Attractor deleted\n");
			  return;
		  }
	  }
  }
  else
  {
	RhinoApp().Print("No valid attractor in that selection\n");
  }
}

void RndPointSet::ViewEdit( const CRhinoCommandContext& context )
{
  CRhinoGetObject getPoint;

  const ON_Point* ptAttractor;
  const ON_Curve* curveAttractor;

  getPoint.SetCommandPrompt( L"Select attractor to view and edit" );
  getPoint.GetObjects(1,1);
  if((ptAttractor = getPoint.Object(0).Point()) != NULL) //did it work?
  {
	  //RhinoApp().Print("got point\n");
	  //RhinoApp().Print("pt %f %f %f\n", attractor.x, attractor.y, attractor.z);
	  unsigned int j;
	  for(j = 0; j < pointAttractors.size(); j++)
	  {
		  //RhinoApp().Print("attr: %f %f %f\n", pointAttractors.at(j).point.x, pointAttractors.at(j).point.y, pointAttractors.at(j).point.z);
		  if(pointAttractors.at(j).point == ptAttractor->point)
		  {
			  RhinoApp().Print("Point #%d: x=%.2f y=%.2f z=%.2f Current strength: %f\n", j, pointAttractors.at(j).point.x, pointAttractors.at(j).point.y, pointAttractors.at(j).point.z, pointAttractors.at(j).strength);

			  CRhinoGetString getNumber;
			  double newStrength = NULL;

			  getNumber.SetCommandPrompt( L"Enter new attractor value, or leave blank to keep current value" );
			  getNumber.AcceptNothing();
			  if(getNumber.GetString() == CRhinoGetString::nothing)
			  {
				RhinoApp().Print("Value unchanged\n");
				return;
			  }
			  newStrength = _wtof(getNumber.String());

			  if(newStrength != NULL)
			  {
				pointAttractors.at(j).strength = newStrength;
				RhinoApp().Print("Strength set to %f\n", pointAttractors.at(j).strength);
			  }
			  return;
		  }
	  }
  }
  else if((curveAttractor = getPoint.Object(0).Curve()) != NULL) //did it work?
  {
	  //RhinoApp().Print("got curve\n");
	  //RhinoApp().Print("pt %f %f %f\n", attractor.x, attractor.y, attractor.z);
	  unsigned int j;
	  for(j = 0; j < curveAttractors.size(); j++)
	  {
		  //RhinoApp().Print("attr: %f %f %f\n", pointAttractors.at(j).point.x, pointAttractors.at(j).point.y, pointAttractors.at(j).point.z);
		  if(curveAttractors.at(j).GetCurve() == curveAttractor)
		  {
			  RhinoApp().Print("Curve #%d: Current strength: %f\n", j, curveAttractors.at(j).strength);

			  CRhinoGetString getNumber;
			  double newStrength = NULL;

			  getNumber.SetCommandPrompt( L"Enter new attractor value, or leave blank to keep current value" );
			  getNumber.AcceptNothing();
			  if(getNumber.GetString() == CRhinoGetString::nothing)
			  {
				RhinoApp().Print("Value unchanged\n");
				return;
			  }
			  newStrength = _wtof(getNumber.String());

			  if(newStrength != NULL)
			  {
				curveAttractors.at(j).strength = newStrength;
				RhinoApp().Print("Strength set to %f\n", curveAttractors.at(j).strength);
			  }
			  return;
		  }
	  }
  }
  else
  {
	RhinoApp().Print("No valid attractor in that selection\n");
  }
}

void RndPointSet::RunVoronoi(const CRhinoCommandContext& context, bool drawCellLines, float minDist, float offset)
{
	  AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	//RhinoApp().Print(L"\n in runvoronoi \n");
	  const ON_Surface* obj = surface;
	  ON_Brep* brep = obj->BrepForm();
	  RhinoApp().Print(L"offset: %f", offset);
	  float x1,y1,x2,y2;
	  struct Site *s1;
	  struct Site *s2;
	  struct GraphEdge* ge;
	  ON_3dPoint p1;
	  ON_3dPoint p2;
	  VoronoiDiagramGenerator vdg;
	  //CellBorder cb;
	  double umin, umax, vmin, vmax;
	  obj->GetDomain(0, &umin, &umax);
	  obj->GetDomain(1, &vmin, &vmax);
	  //RhinoApp().Print(L"\n start gen \n");
	  //RhinoApp().Print(L"\n vsize: %d umin: %f umax: %f vmin: %f vmax: %f\n",vsize, umin, umax, vmin, vmax);
	  if(xValues == NULL || yValues == NULL )
	  {
		RhinoApp().Print(L"\n NULL ARRAY \n");
	  }
	  /*for(int k=0; k<vsize; k++)
      {
		RhinoApp().Print(L"\n u,v : %f,%f \n"),xValues[k],yValues[k];
	  }*/

	  vdg.generateVoronoi(xValues,yValues,vsize, (float)umin, (float)umax, (float)vmin, (float)vmax, minDist); 
	  vdg.resetIterator();
	  rndPoints.clear();
	  //rndPoints = new ON_SimpleArray<ON_2dPoint>[vsize];
	  RhinoApp().Print(L"\n start ittr \n");
	  for(int i=0; i<vsize; i++)
	  {
		  rndPoints.push_back(ON_SimpleArray<ON_2dPoint>());
	  }
	  RhinoApp().Print(L"\n-------------------------------\n");
	 
	  //while(vdg.getNext(x1,y1,x2,y2,s1,s2))
	  ON_SimpleArray<ON_2dPoint> pointArr;
	  ON_2dPoint first;
	  ON_2dPoint second;
	  ON_Curve* item;
	  CRhinoCurveObject* temp;
	  int pointCount = 0 ;
	  while((ge = vdg.getNext2()))
	  {
		  if(ge->reg[0] != NULL && ge->reg[1] != NULL)
		  {
			edgeList.push_back(ge);
		  }
	  }
	  //RhinoApp().Print(L"Edges: %d\n", edgeList.size());
	  vdg.resetIterator();
	  struct GraphEdge* ge1 = NULL;
	  struct GraphEdge* ge2 = NULL;
	  struct GraphEdge* cur = NULL;
	  while((ge = vdg.getNext2()))
	  {	
		  x1 = ge->x1;
		  y1 = ge->y1;
		  x2 = ge->x2;
		  y2 = ge->y2;
		  s1 = ge->reg[0]; //bisected points
		  s2 = ge->reg[1]; 
		  //RhinoApp().Print(L"here\n");
		  //RhinoApp().Print(L"Number %d and %d:: %f,%f \t||\t %f,%f \t || \t %d, %d\n",s1->sitenbr, s2->sitenbr,s1->coord.x,s1->coord.y,s2->coord.x,s2->coord.y, s1->sitenbr, s2->sitenbr);
		  //RhinoApp().Print(L"%d, %d\n", s1.sitenbr, s2.sitenbr);
		 
			first = ON_2dPoint(x1, y1);
			second = ON_2dPoint(x2, y2);
			//draw line

			pointArr.Append(first);
			pointArr.Append(second);		

			item = RhinoInterpolatePointsOnSurface(*obj, pointArr, 0, .01, 0);
			if(item != NULL)//draw the cells
			{
			   temp = context.m_doc.AddCurveObject(*item);
			   cellLines.push_back(temp);
					if(!drawCellLines)
						context.m_doc.HideObject(temp);
			}
			pointArr.Destroy();

			//find the site that the edge relates to, if it can be drawn
		  if(s1 != (struct Site *)NULL && s2 != (struct Site *)NULL && item != (ON_Curve *)NULL)
		  {
			  
			  //RhinoApp().Print(L"S1:%d\n", s1->sitenbr);
				float u = s1->coord.x;
				float v = s1->coord.y;
				int index = -1;
				//search for matching random point
				for(int i=0; i<vsize; i++)
				{
					if(xValues[i] == u && yValues[i] == v)
					{
						//found match
						index = i;
						//RhinoApp().Print(L"%d\n", index);
						break;
					}
				}
				if(index == -1)
				{
					//no match found
					RhinoApp().Print(L"No matching point");
				}else
				{
					ON_2dPoint offsetPoint;// = ON_2dPoint( x1/2 + x2/2, y1/2 + y2/2);
					//move endpoints along vector towards center point
					float midx = x1/2 + x2/2;
					float midy = y1/2 + y2/2;
					float dist = sqrt(pow((xValues[index] - midx), 2) + pow((yValues[index] - midy), 2));
					float xvec = (xValues[index] - midx)/dist;
					float yvec = (yValues[index] - midy)/dist;
					offsetPoint = ON_2dPoint( midx + xvec * offset, midy + yvec * offset);
					rndPoints.at(index).Append(offsetPoint);
					pointCount++;
					//ON_3dPoint p0 = surface->PointAt( offsetPoint.x, offsetPoint.y);
					//points.push_back(context.m_doc.AddPointObject(p0));
					/*dist = sqrt(pow((xValues[index] - x2), 2) + pow((yValues[index] - y2), 2));
					xvec = (xValues[index] - x2) /dist;
					yvec = (yValues[index] - y2) /dist;
					offsetPoint = ON_2dPoint( x2 + xvec * offset, y2 + yvec* offset);
					rndPoints.at(index).Append(offsetPoint);*/
				}

				//RhinoApp().Print(L"S2:%d\n", s2->sitenbr);
			   u = s2->coord.x;
			   v = s2->coord.y;
				index = -1;
				//search for matching random point
				for(int i=0; i<vsize; i++)
				{
					if(xValues[i] == u && yValues[i] == v)
					{
						//found match
						index = i;
						break;
					}
				}
				if(index == -1)
				{
					//no match found
					RhinoApp().Print(L"No matching point");
				}else
				{
					ON_2dPoint offsetPoint;// = ON_2dPoint( x1/2 + x2/2, y1/2 + y2/2);
					//move endpoints along vector towards center point
					float midx = x1/2 + x2/2;
					float midy = y1/2 + y2/2;
					float dist = sqrt(pow((xValues[index] - midx), 2) + pow((yValues[index] - midy), 2));
					float xvec = (xValues[index] - midx)/dist;
					float yvec = (yValues[index] - midy)/dist;
					offsetPoint = ON_2dPoint( midx + xvec * offset, midy + yvec * offset);
					rndPoints.at(index).Append(offsetPoint);
					pointCount++;
					//ON_3dPoint p0 = surface->PointAt( offsetPoint.x, offsetPoint.y);
					//points.push_back(context.m_doc.AddPointObject(p0));
					/*dist = sqrt(pow((xValues[index] - x2), 2) + pow((yValues[index] - y2), 2));
					xvec = (xValues[index] - x2) /dist;
					yvec = (yValues[index] - y2) /dist;
					offsetPoint = ON_2dPoint( x2 + xvec * offset, y2 + yvec* offset);
					rndPoints.at(index).Append(offsetPoint);*/
				}
		  }
		  //border edge
		  if((struct Site *)s1 == NULL && (struct Site *)s2 == NULL)
		  {
			  //RhinoApp().Print(L"here border\n");
			//search edgelist for matching endpoints
			  ge1 = NULL;
			  ge2 = NULL;
			  cur = NULL;
			  for(int j=0; j < edgeList.size(); j++)
			  {
				  
				  cur = edgeList.at(j);
				  if(cur== NULL)
				  {
					RhinoApp().Print(L"null graph edge\n");
				  }
				  else if(x1 == cur->x1 && y1 == cur->y1)
				  {
					  if(ge1 != NULL)
					  {
						  ge2 = cur;
						  break;
					  }else
					  {
						  ge1 = cur;
					  }

				  }else if(x1 == cur->x2 && y1 == cur->y2)
				  {
					  if(ge1 != NULL)
					  {
						  ge2 = cur;
						  break;
					  }else
					  {
						  ge1 = cur;
					  }
				  }else if(x2 == cur->x1 && y2 == cur->y1)
				  {
					  if(ge1 != NULL)
					  {
						  ge2 = cur;
						  break;
					  }else
					  {
						  ge1 = cur;
					  }

				  }else if(x2 == cur->x2 && y2 == cur->y2)
				  {
					  if(ge1 != NULL)
					  {
						  ge2 = cur;
						  break;
					  }else
					  {
						  ge1 = cur;
					  }
				  }
			  }
			  if(ge1 == NULL || ge2 == NULL)
			  {
				RhinoApp().Print(L"Border edge missing connection");
			  }else
			  {
				//find the common point
				  float u, v = 0;
				  int index = -1;
				  if(ge1->reg[0]->coord.x == ge2->reg[0]->coord.x || ge1->reg[0]->coord.x == ge2->reg[1]->coord.x)
				  {
					  u = ge1->reg[0]->coord.x;
				  }else if(ge1->reg[1]->coord.x == ge2->reg[0]->coord.x || ge1->reg[1]->coord.x == ge2->reg[1]->coord.x)
				  {
					  u = ge1->reg[1]->coord.x;
				  }else
				  {
					  RhinoApp().Print(L"Border edge point mismatch");
				  }

				  if(ge1->reg[0]->coord.y == ge2->reg[0]->coord.y || ge1->reg[0]->coord.y == ge2->reg[1]->coord.y)
				  {
					  v = ge1->reg[0]->coord.y;
				  }else if(ge1->reg[1]->coord.y == ge2->reg[0]->coord.y || ge1->reg[1]->coord.y == ge2->reg[1]->coord.y)
				  {
					  v = ge1->reg[1]->coord.y;
				  }else
				  {
					  RhinoApp().Print(L"Border edge point mismatch");
				  }

				  //search for matching random point
					for(int i=0; i<vsize; i++)
					{
						if(xValues[i] == u && yValues[i] == v)
						{
							//found match
							index = i;
							break;
						}
					}
					if(index == -1)
					{
						//no match found
						//RhinoApp().Print(L"No matching point");
					}else
					{
						//RhinoApp().Print(L"placing border point\n");
						ON_2dPoint offsetPoint;// = ON_2dPoint( x1/2 + x2/2, y1/2 + y2/2);
						//move endpoints along vector towards center point
						float midx = x1/2 + x2/2;
						float midy = y1/2 + y2/2;
						float dist = sqrt(pow((xValues[index] - midx), 2) + pow((yValues[index] - midy), 2));
						float xvec = (xValues[index] - midx)/dist;
						float yvec = (yValues[index] - midy)/dist;
						offsetPoint = ON_2dPoint( midx + xvec * offset, midy + yvec * offset);
						rndPoints.at(index).Append(offsetPoint);
						//ON_3dPoint p0 = surface->PointAt( offsetPoint.x, offsetPoint.y);
						//points.push_back(context.m_doc.AddPointObject(p0));
						
					}
			  }
		  }
		  
	  }
	  //RhinoApp().Print(L"end while");
	  //RhinoApp().Print(L"PointCount: %d", pointCount);
	  //RhinoApp().Print(L"HERE2");
	  
	  //draw trim curves
	  for(int i=0; i<vsize; i++)
      {
			avgU = 0;
			avgV = 0;
			//find the center of the points
			for(int j=0; j < rndPoints.at(i).Count(); j++)
			{
				avgU += rndPoints.at(i).At(j)->x;
				avgV += rndPoints.at(i).At(j)->y;
			}
			avgU = avgU / rndPoints.at(i).Count();
			avgV = avgV / rndPoints.at(i).Count();
			rndPoints.at(i).QuickSort(&sortPoints);
			//rndPoints.at(i).QuickSort(ON_CompareIncreasing);
			ON_Curve* item = RhinoInterpolatePointsOnSurface(*obj, rndPoints.at(i), 1, .001, 0);
			//trimming code
			if(item != NULL)
			{
				surfaceCurves.push_back(context.m_doc.AddCurveObject(*item));
				curveArr.Append(item);
			}else
			{
				//RhinoApp().Print(L"no projection");
			}
	  }
	  //RhinoApp().Print(L"HERE3");
	  

	  //delete(xValues);
	  //delete(yValues);
	  context.m_doc.Redraw();
}
void RndPointSet::TrimBrep( const CRhinoCommandContext& context )
{
	CRhinoGetObject go;
	go.SetCommandPrompt( L"Select surface to trim" );
	go.SetGeometryFilter( CRhinoGetObject::surface_object);
	go.GetObjects( 1, 1 );

	// Get the surface geometry
	const ON_Brep* ref = go.Object(0).Brep();
	//ref->CullUnusedFaces();
	for(int i=0; i < ref->m_F.SizeOf(); i++)
	{
		
		ON_Brep* split = RhinoSplitBrepFace(*ref, i , curveArr, .001, true);
		if (split==NULL)
		{
		  //RhinoApp().Print(L"split failed");
		}else
		{
		  RhinoApp().Print(L"split worked");
		  trimmedBrep = context.m_doc.AddBrepObject(*split);
		}
		
		
	}
	
}

void RndPointSet::UndoTrim( const CRhinoCommandContext& context )
{
	if(trimmedBrep != NULL)
	{
		context.m_doc.DeleteObject(trimmedBrep);
		trimmedBrep = NULL;
	}
}
int sortPoints(const ON_2dPoint* p1, const ON_2dPoint* p2)
{
	if (p1->x >= 0 && p2->x < 0)
        return -1;
    if (p1->x == 0 && p2->x == 0)
        return p1->y > p2->y;

    // compute the cross product of vectors (center -> a) x (center -> b)
    float det = (p1->x-avgU) * (p2->y - avgV) - (p2->x - avgU) * (p1->y - avgV);
    if (det < 0)
        return 1;
    if (det > 0)
        return -1;

    // points a and b are on the same line from the center
    // check which point is closer to the center
    int d1 = (p1->x-avgU) * (p1->x-avgU) + (p1->y-avgV) * (p1->y-avgV);
    int d2 = (p2->x-avgU) * (p2->x-avgU) + (p2->y-avgV) * (p2->y-avgV);
    return d1 > d2;
}
void RndPointSet::DrawPoints( const CRhinoCommandContext& context, unsigned int numPoints, double overallStrength )
{
  // Pick a surface to evaluate
  CRhinoGetObject go;
  go.SetCommandPrompt( L"Select surface to evaluate " );
  go.SetGeometryFilter( CRhinoGetObject::surface_object);
  go.GetObjects( 1, 1 );
  vsize = numPoints;

  // Get the surface geometry
  const CRhinoObjRef& ref = go.Object(0);
  if(ref == NULL)
  {
	RhinoApp().Print(L"reference initialization error");
	return ;
  }
  const ON_Surface* obj = ref.Surface();
  if(obj == NULL)
  {
	RhinoApp().Print(L"object initialization error");
	return ;
  }	
  mainBrep = ref.Brep();
  surface = obj;
  
  //Erase check and check if the surfaces match
  if(pointAttractors.size() > 0)
  {
	  //removed deleted attractors
	  unsigned int j;
	  for(j = 0; j < pointAttractors.size(); j++)
	  {
		  if(&(pointAttractors.at(j).pointObj->Point()) == NULL || !pointAttractors.at(j).CheckSurface(surface))
		  {
			  RhinoApp().Print("\nErasing bad point attractor");
			  pointAttractors.erase(pointAttractors.begin() + j);
		  }
	  }
  }
  if(curveAttractors.size() > 0)
  {
	  //removed deleted attractors
	  unsigned int j;
	  for(j = 0; j < curveAttractors.size(); j++)
	  {
		  if(curveAttractors.at(j).GetObjRef().Curve() == NULL || !curveAttractors.at(j).CheckSurface(surface))
		  {
			  RhinoApp().Print("\nErasing deleted curve attractor");
			  curveAttractors.erase(curveAttractors.begin() + j);
		  }
	  }
  }
    
  if(EvaluateAttractorsManyVectors(context, numPoints, overallStrength))
  {
	  unsigned int i;
	  for(i = 0; i < pointAttractors.size(); i++)
	  {
		  context.m_doc.DeleteObject(pointAttractors.at(i).pointObj);
	  }
	  for(i = 0; i < curveAttractors.size(); i++)
	  {
		  context.m_doc.DeleteObject(curveAttractors.at(i).GetObjRef());
	  }
	  context.m_doc.Redraw();
	  pointsHidden = false;
  }
  else
  {
	RhinoApp().Print(L"object domain error");
  }
}

bool RndPointSet::EvaluateAttractorsManyVectors(const CRhinoCommandContext& context, unsigned int numPoints, double overallStrength)
{
  double u1, u2, v1, v2;
  if(surface->GetDomain(0, &u1, &u2) && surface->GetDomain(1, &v1, &v2))
  {
	  xValues = new float[numPoints];
	  yValues = new float[numPoints];
	  unsigned int i;
	  ON_3dPoint prev;
	  for(i = 0; i < numPoints; i++)
	  {
		  ON_3dPoint p0;
		  double u, v = 0.0;
		  p0 = surface->PointAt( u = fRand(u1, u2), v = fRand(v1, v2));
		  //RhinoApp().Print(L"p0.x = %f ",p0.x);
		  //RhinoApp().Print(L"p0.y = %f ",p0.y);
		  //RhinoApp().Print(L"p0.z = %f ",p0.z);
		  //RhinoApp().Print(L"p0.u = %f ",u);
		  //RhinoApp().Print(L"p0.v = %f ",v);

		  //RhinoApp().Print(L" adding: %f,%f aka %f %f %f\n",(float)u,(float)v, p0.x, p0.y, p0.z);
		  //RhinoApp().Print(L"p0.u = %f\n",u);
		  //RhinoApp().Print(L"p0.v = %f\n",v);

		  //deal with attractors
		  
		  if(pointAttractors.size() + curveAttractors.size() > 0)
		  {
			  
			  double uChange = 0;
			  double vChange = 0;

			  unsigned int j;
			  for(j = 0; j < pointAttractors.size(); j++)
			  {
				  pointAttractors.at(j).Shift(u, v, &uChange, &vChange, overallStrength);
			  }
			  for(j = 0; j < curveAttractors.size(); j++)
			  {
				  PointAttractor pa;
				  curveAttractors.at(j).GetClosestPointAttractor(p0, &pa);
				  if(&pa != NULL)
					  pa.Shift(u, v, &uChange, &vChange, overallStrength);
			  }
			  u += uChange;
			  v += vChange;

			  //make sure the values aren't out of bounds
			  if(u < u1) u = u1;
			  else if(u > u2) u = u2;
			  if(v < v1) v = v1;
			  else if(v > v2) v = v2;
		  }
		  //add this point to the data set
		  xValues[i] = (float)(u);
		  yValues[i] = (float)(v);
		  p0 = surface->PointAt(u, v);

		  points.push_back(context.m_doc.AddPointObject(p0));
	  }
	  return true;
  }
  else
  {
	return false;
  }
}

void RndPointSet::ToggleHidePoints(const CRhinoCommandContext& context, bool drawCellLines)
{
	unsigned int i;
	if(pointsHidden)
	{
	  pointsHidden = false;
	  RhinoApp().Print(L"Points/lines displayed\n");
	  for(i = 0; i < points.size(); i++)
	  {
		  context.m_doc.ShowObject(points.at(i));

	  }
	  if(drawCellLines)
	  {
		  for(i = 0; i<cellLines.size(); i++)
		  {
			  context.m_doc.ShowObject(cellLines.at(i));
		  }
	  }
	}
	else
	{
	  pointsHidden = true;
	  RhinoApp().Print(L"Points/lines hidden\n");
	  for(i = 0; i < points.size(); i++)
	  {
		  context.m_doc.HideObject(points.at(i));
	  }
	  for(i = 0; i<cellLines.size(); i++)
	  {
		  context.m_doc.HideObject(cellLines.at(i));
	  }
	}
	context.m_doc.Redraw();
}

void RndPointSet::BurnData(const CRhinoCommandContext& context)
{
	rndPoints.clear();
	//cellBorderList.clear();
	pointAttractors.clear();
	curveAttractors.clear();
	points.clear();
	cellLines.clear();
	surfaceCurves.clear();
	if(trimmedBrep != NULL)
	{
		context.m_doc.DeleteObject(trimmedBrep);
		trimmedBrep = NULL;
	}

	context.m_doc.Redraw();

	RhinoApp().Print("\nData burned");
}

void RndPointSet::ClearAll(const CRhinoCommandContext& context)
{
	unsigned int i;

	for(i = 0; i < pointAttractors.size(); i++)
	{
	  context.m_doc.DeleteObject(pointAttractors.at(i).pointObj);
	}
	for(i = 0; i < curveAttractors.size(); i++)
	{
	  context.m_doc.DeleteObject(curveAttractors.at(i).GetObjRef());
	}
	for(i = 0; i < points.size(); i++)
	{
	  context.m_doc.DeleteObject(points.at(i));
	}
	for(i = 0; i < cellLines.size(); i++)
	{
	  context.m_doc.DeleteObject(cellLines.at(i));
	}
	for(i = 0; i < surfaceCurves.size(); i++)
	{
	  context.m_doc.DeleteObject(surfaceCurves.at(i));
	}
	if(trimmedBrep != NULL)
	{
		context.m_doc.DeleteObject(trimmedBrep);
		trimmedBrep = NULL;
	}
	rndPoints.clear();
	//cellBorderList.clear();
	pointAttractors.clear();
	curveAttractors.clear();
	points.clear();
	cellLines.clear();
	surfaceCurves.clear();

	context.m_doc.Redraw();

	RhinoApp().Print("\nData cleared");
}

void RndPointSet::UndoCurves(const CRhinoCommandContext& context)
{
	unsigned int i;

	for(i = 0; i < points.size(); i++)
	{
	  context.m_doc.ShowObject(points.at(i));
	}
	for(i = 0; i < cellLines.size(); i++)
	{
	  context.m_doc.DeleteObject(cellLines.at(i));
	}
	for(i = 0; i < surfaceCurves.size(); i++)
	{
	  context.m_doc.DeleteObject(surfaceCurves.at(i));
	}

	//cellBorderList.clear();
	cellLines.clear();
	surfaceCurves.clear();
	rndPoints.clear();
	curveArr.Destroy();
	context.m_doc.Redraw();

	RhinoApp().Print("\nCurves cleared");
}

void RndPointSet::UndoPoints(const CRhinoCommandContext& context)
{
	unsigned int i;

	for(i = 0; i < pointAttractors.size(); i++)
	{
	  pointAttractors.at(i).pointObj = context.m_doc.AddPointObject(pointAttractors.at(i).point);
	}
	for(i = 0; i < curveAttractors.size(); i++)
	{
	  curveAttractors.at(i).SetObjRef(context.m_doc.AddCurveObject(*(curveAttractors.at(i).GetCurve())));
	}
	for(i = 0; i < points.size(); i++)
	{
	  context.m_doc.DeleteObject(points.at(i));
	}

	points.clear();

	context.m_doc.Redraw();

	RhinoApp().Print("\nPoints cleared");
}


double RndPointSet::fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}