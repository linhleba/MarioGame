#pragma once
#include "GameObject.h"
#define SCORE_BBOX_WIDTH  0
#define SCORE_BBOX_HEIGHT 0
class CScore : public CGameObject
{
private:
	bool isScoreCounted = false;

	DWORD isMoving_start;
	bool isMoving = false;

	// 0 = not set, level 1:100, level 2:200 ... respectively
	int levelOfScore = 0;
public:
	CScore();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);

	void SetScore(int value, double x, double y);
};

