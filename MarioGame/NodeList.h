#pragma once
#include "GameObject.h"
#include "Node.h"
class NodeList : public CGameObject
{
	vector<CNode*> listOfNodes;
	int sumOfNodes = 0;
	int currentDirectID = 1;
public:
	void SetTheDirection();
	int findTheDirection(int dir);

};

