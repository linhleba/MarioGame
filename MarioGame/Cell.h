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
	void AddObjectIntoCell(LPGAMEOBJECT object) { listGameObjectCell.emplace_back(object); }
	vector<LPGAMEOBJECT> GetListGameObjectCell() { return listGameObjectCell; }
};


typedef Cell* LPCELL;


