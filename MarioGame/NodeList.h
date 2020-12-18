#pragma once
#include "GameObject.h"
#include "Node.h"
#include "Utils.h"
class CNodeList : public CGameObject
{
	vector<CNode*> listOfNodes;
	int currentID = 6;
	//bool openingGate = true;
public:
	virtual void Render();
	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void AddNode(CNode* node);
	void SetTheDirection();
	bool FindTheDirection(int dir);
	void SetListOfNodes(vector<CNode*> listOfNodes) { this->listOfNodes = listOfNodes; }
	//void SetCurrentNode();
	void DebugDirection()
	{
		for (size_t i = 0; i < listOfNodes.size(); i++)
		{
			int bottom = listOfNodes.at(i)->GetDirection(VECTOR_INDEX_RIGHT_DIRECTION);
			//DebugOut(L"chi so i la %d \n", i + 1);
			DebugOut(L"right direction la %d \n", bottom);
		}
	}

	~CNodeList();
};

