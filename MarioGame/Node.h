#pragma once
#include "GameObject.h"
class CNode : public CGameObject
{
protected:
	int id; 
	vector<int> direction;
public:
	CNode();
	int GetId() { return id; }
	int GetDirection(int dir) { return direction.at(dir); }

	void SetDirection(int value, int typeOfDirection) { direction.at(typeOfDirection) = value; }
};

