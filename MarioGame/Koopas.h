#pragma once

#include "GameObject.h"
#include "define.h"

class CKoopas : public CGameObject
{
private:
	bool isHeld = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CKoopas();
	virtual void SetState(int state);
	void SetBeingHolding(bool value) { isHeld = value; }
};