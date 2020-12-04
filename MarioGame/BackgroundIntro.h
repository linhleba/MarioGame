#pragma once
#include "GameObject.h"


class CBackgroundIntro : public CGameObject
{
private: 
	int typeOfBackground;
	int vibrateDirect = -1;

	DWORD timeBackgroundDown_start;
	bool isTimeBackgroundDown = false;

	DWORD timeVibrating_start;
	bool isTimeVibrating = false;

	// check to end of second background intro
	bool isEndingSecondBackground = false;
public:
	CBackgroundIntro(int type);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void SetState(int state);

	int GetTypeOfBackground() { return typeOfBackground; }
	int GetIsEndingSecondBackground() { return isEndingSecondBackground; }
};
