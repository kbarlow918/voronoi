#include "StdAfx.h"
#include "Cell.h"
//#include <cmath>

Cell::Cell(void)
{
}

Cell::~Cell(void)
{
}

Cell::Cell(std::vector<CellBorder> cbl)
{
	int i = 0;
	for(i; i<(int)cbl.size();i++)
	{
		cellEdges.push_back(cbl.at(i));
	}
}

std::vector<CellBorder> Cell::getEdges()
{
	return cellEdges;
}

bool Cell::isEqual(Cell c)
{
	std::vector<CellBorder> cedges = c.getEdges();
	CellBorder cb = CellBorder();
	int same = 0;
	int h = 0;
	int i = 0;
	for(h; h<(int)cellEdges.size();h++)
	{
		for(i; i<(int)cedges.size();i++)
		{
			cb = cedges.at(i);
			if(cb.isEqual(cellEdges.at(h)))
			{
				same++;
			}
		}
	}
	if( same > 1)
	{
		return true;
	}
	return false;
}
