#pragma once

#include "GameObject.h"
#include "define.h"

class CKoopas : public CGameObject
{
private:
	// check is face up or not
	bool isFaceUp = false;
	
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

	// set is able fall is false if type of Koopas is red and walking status
	bool isAbleFall = true;
	double prePositionOnGround;

	// set direction die fall
	int dieFallDirection = 1;
	
	// declear intro scene
	bool isBeingGreenHolding = false;
	bool isBeingRedHolding = false;

	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CKoopas(int type);
	virtual void SetState(int state);
	void SetBeingHolding(bool value) { isHeld = value; }
	void SetIsBeingGreenHolding(bool value) { isBeingGreenHolding = value; }
	void SetIsBeingRedHolding(bool value) { isBeingRedHolding = value; }

	void SetIsFaceUp(bool value) { isFaceUp = value; }
	bool GetIsFaceUp() { return isFaceUp; }
	void UpdatePositionHeld();
};