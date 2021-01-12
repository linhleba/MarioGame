#pragma once
#include "Cell.h"
#include "Mario.h"


//typedef Grid* LPGRID;
#define MAX_GRID_LINE	1024
class Grid
{
	//vector<LPGAMEOBJECT> listGameObjectGrid;
	int sizeOfCell;
	int numOfColumns;
	int numOfRows;
	Cell** cells;

	int currentLeftRow = -1;
	int currentRightRow = -1;
	int currentTopColumn = -1;
	int currentBottomColumn = -1;
public:
	Grid();
	Grid(LPCWSTR path);
	void HandleGrid(vector<LPGAMEOBJECT>* coObjects, double camX, double camY, double screenWidth, double screenHeight);
	void _ParseSection_SETTINGS(string line);
	void _PareseSection_OBJECTS(string line);
	//vector<LPGAMEOBJECT> GetObjectsInGrid() { return listGameObjectGrid; }
	void UpdateCell();
	~Grid();
};

