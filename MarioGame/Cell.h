#pragma once
#include "GameObject.h"
#include "Game.h"
class Cell
{
	bool isActive;
	vector<LPGAMEOBJECT> listGameObjectCell;
public:
	Cell();
	~Cell();
	void AddObjectIntoCell(LPGAMEOBJECT object) { listGameObjectCell.push_back(object); }
	vector<LPGAMEOBJECT> GetListGameObjectCell() { return listGameObjectCell; }
};


typedef Cell* LPCELL;


