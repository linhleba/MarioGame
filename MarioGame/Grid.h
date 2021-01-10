#pragma once
#include "Cell.h"
#include "Mario.h"


//typedef Grid* LPGRID;
#define MAX_GRID_LINE	1024
class Grid
{
	vector<LPGAMEOBJECT> listGameObjectGrid;
	int sizeOfCell;
	int numOfColumns;
	int numOfRows;
	Cell** cells;
public:
	Grid();
	Grid(LPCWSTR path);
	void HandleGrid();
	void _ParseSection_SETTINGS(string line);
	void _PareseSection_OBJECTS(string line);
	vector<LPGAMEOBJECT> GetObjectsInGrid() { return listGameObjectGrid; }
	~Grid();
};

