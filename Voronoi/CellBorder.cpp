#include "StdAfx.h"
#include "CellBorder.h"
//#include <cmath>

CellBorder::CellBorder(void)
{
}

CellBorder::~CellBorder(void)
{
}

CellBorder::CellBorder(ON_2dPoint p0, ON_2dPoint p1)
{
	start = p0;
	end = p1;
}
void CellBorder::findConnected(std::vector<CellBorder> cbl)
{
	int i = 0;
	int size = (int) cbl.size();
	CellBorder temp;
	for(i;i<size;i++)
	{
		temp = cbl.at(i);
		if( isConnected(temp) && !isEqual(temp) )
		{
			connectedBorders.push_back(temp);
		}
	}
}
bool CellBorder::isConnected(CellBorder cb)
{
	if(((cb.start.x == start.x) && (cb.start.y == start.y)) || ((cb.start.x == end.x) && (cb.start.y == end.y)))
	{
		return true;
	}
	if(((cb.end.x == start.x) && (cb.end.y == start.y)) || ((cb.end.x == end.x) && (cb.end.y == end.y)))
	{
		return true;
	}
	return false;
}
bool CellBorder::isEqual(CellBorder cb)
{
	if(((cb.start.x == start.x) && (cb.start.y == start.y)) && ((cb.end.x == end.x) && (cb.end.y == end.y)))
	{
		return true;
	}
	if(((cb.end.x == start.x) && (cb.end.y == start.y)) && ((cb.start.x == end.x) && (cb.start.y == end.y)))
	{
		return true;
	}
	return false;
}
