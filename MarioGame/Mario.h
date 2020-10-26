#pragma once
#include "GameObject.h"
#include "define.h"



class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	bool hasTurnBackTail = false;
	DWORD turnBackTail_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
	float boostSpeed = 0;

	bool isJumping = false;
	int  shoot = 0;  // -1 right 1 left
	bool isHolding = false;  // false is not holding, true is holding

public:
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void SetBoostSpeed(float x) { boostSpeed = x; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartTurningBack() { turnBackTail_start = GetTickCount(); hasTurnBackTail = true; }

	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	bool IsJumping() { return isJumping; }
	void SetIsJumping(bool value);
	int GetLevel() { return level; };
	bool CheckStateFlying();
	bool HasTurnBackTail() { return hasTurnBackTail; }
	void SetTurnBackTail(bool value) { hasTurnBackTail = value; }
	void SetIsHolding(bool value) { isHolding = value; }

};