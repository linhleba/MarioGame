#pragma once
#include "GameObject.h"
class CObjectWorldMap : public CGameObject
{
	int typeOfObject;

	DWORD isHelp_start;
	bool checkIsHelpStart = false;

	DWORD isDigger_start;
	bool checkIsDiggerStart = false;
public:
	CObjectWorldMap(int type);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void SetState(int state);
};

