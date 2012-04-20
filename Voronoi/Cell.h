#pragma once
#include <vector>
#include "CellBorder.h"
class Cell
{
public:
	Cell(void);
	~Cell(void);
	Cell(std::vector<CellBorder> cbl);
	std::vector<CellBorder> getEdges();

private:
	std::vector<CellBorder> cellEdges;
	bool isEqual(Cell c);
	
};
