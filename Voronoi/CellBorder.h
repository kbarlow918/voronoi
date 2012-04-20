#pragma once
#include <vector>
class CellBorder
{
public:
	CellBorder(void);
	~CellBorder(void);
	CellBorder(ON_2dPoint p0, ON_2dPoint p1);
	void findConnected(std::vector<CellBorder> cbl);
	std::vector<CellBorder> connectedBorders;
	bool isEqual(CellBorder cb);

	ON_2dPoint start;
	ON_2dPoint end;
    
private:
	
	bool isConnected(CellBorder cb);
	
};
