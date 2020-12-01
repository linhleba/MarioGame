#pragma once

#include "GameObject.h"
#include "define.h"

class CKoopas : public CGameObject
{
private:
	bool isHeld = false;
	DWORD timeRenew_start;
	bool isRenewStart = false;

	// time between renew the Koopas and the state of the Koopas walking
	DWORD timeWalking_start;

	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CKoopas();
	virtual void SetState(int state);
	void SetBeingHolding(bool value) { isHeld = value; }
};