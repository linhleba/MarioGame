#pragma once
#include "GameObject.h"

#define QUESTION_BBOX_WIDTH  16
#define QUESTION_BBOX_HEIGHT 16

class CQuestion : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	CQuestion();

	int CheckPositionQuestion();
};