#pragma once

#include "GameObject.h"
#include "define.h"

class CKoopas : public CGameObject
{
private:
	int typeOfKoopas;
	bool isHeld = false;

	// time to renew Koopas, set when state Koopas is die
	DWORD timeRenew_start;
	bool isRenewStart = false;

	// time between renew the Koopas and the state of the Koopas walking
	DWORD timeWalking_start;

	// time to Koopas flying
	DWORD timeFlying_start;
	bool isFLying = false;

	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CKoopas(int type);
	virtual void SetState(int state);
	void SetBeingHolding(bool value) { isHeld = value; }
};