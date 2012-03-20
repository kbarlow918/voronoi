#pragma once
#include <vector>
class CellBorder
{
public:
	CellBorder(void);
	~CellBorder(void);
	CellBorder(ON_2dPoint p0, ON_2dPoint p1);
	void findConnected(std::vector<CellBorder> cbl);

	ON_2dPoint start;
	ON_2dPoint end;
    
private:
	std::vector<CellBorder> connectedBorders;
	bool isConnected(CellBorder cb);
	bool isEqual(CellBorder cb);
	
};
