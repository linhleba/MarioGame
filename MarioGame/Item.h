#pragma once
#include "GameObject.h"

#define ITEM_BBOX_WIDTH  16
#define ITEM_BBOX_HEIGHT 16

class CItem : public CGameObject
{
private:
	DWORD time_Up_Start;
	bool firstTimeUpStart = false;
	DWORD time_Down_Start = 0;
	int typeOfMushRoom;
public:
	CItem();
	CItem(int type);
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);

	void SetTimeUpStart() { if (!firstTimeUpStart) time_Up_Start = GetTickCount(); };
	void SetTimeDownStart() { time_Down_Start = GetTickCount(); };
	int CheckPositionItem(); 
	int CheckPositionItemIntro();
	int GetTypeOfItem() { return typeOfMushRoom; }
};