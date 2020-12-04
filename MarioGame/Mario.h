#pragma once
#include "GameObject.h"
#include "define.h"



class CMario : public CGameObject
{
	vector<int> generalAniBigMario;
	vector<int> generalAniSmallMario;
	vector<int> generalAniFireMario;
	vector<int> generalAniTailMario;
	vector<int> generalAniGreenMario;



	// define type of mario
	int typeOfMario;
	
	// Check condition in Intro Scene
	bool isAppeared = true;
	bool isGreenAbleWalk = true;
	bool isRedAbleWalk = true;


	int level;
	int untouchable;
	DWORD untouchable_start;
	bool hasTurnBackTail = false;
	DWORD turnBackTail_start;
	bool hasHighSpeed = false;
	DWORD highSpeed_start;

	double start_x;			// initial position of Mario at scene
	double start_y;
	double boostSpeed = 0;

	bool isJumping = false;
	int  shoot = 0;  // 1 right -1 left
	bool isHolding = false;  // false is not holding, true is holding
	bool flagHolding = false;  // true - set ani for holding 

	bool isAbleToFly = false; //false if high-speed is not enough, when fly status - set false when collision
	bool startFlying = false;
	DWORD isFlying_start;
	bool checkFall = false;

	// Set isRunning true if the user holds A
	bool isRunning = false;
	bool shootFire = false;
	bool hasAniShootFire = false;

	// Check highspeed for the first time
	bool isFirstTimeHighSpeed = false;  // false - not high speed, true - first time high speed

	// time for shoot Koopas
	DWORD timeShoot_start;
	bool checkTimeShoot = false;





public:
	CMario(double x = 0.0f, double y = 0.0f);
	CMario(int type, double x = 0.0f, double y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void HandleNoCollision(vector<LPGAMEOBJECT>* coObjects);
	void HandleCollision(vector<LPGAMEOBJECT>* coObjects);
	void HandleState();

	// Handle in Render func
	void SetGeneralAniBigMario(vector<int> &generalAniBigMario);
	void SetGeneralAniSmallMario(vector<int> &generalAniSmallMario);
	void SetGeneralAniFireMario(vector<int>& generalAniFireMario);
	void SetGeneralAniTailMario(vector<int>& generalAniTailMario);
	void SetGeneralAniGreenMario(vector<int>& generalAniGreenMario);
	void HandleGeneralAnimation(vector<int> generalAni, int &ani);

	void SetLevel(int l) { level = l; }
	void SetBoostSpeed(double x) { boostSpeed = x; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartTurningBack() { turnBackTail_start = GetTickCount(); hasTurnBackTail = true; }
	void SetTurnBackTail(bool value) { hasTurnBackTail = value; }
	void SetIsHolding(bool value) { isHolding = value; }
	void SetFlagHolding(bool value) { flagHolding = value; }
	void SetStartFlying() { isFlying_start = GetTickCount(); startFlying = true; }
	void SetCheckFall(bool value) { checkFall = value; }
	void SetIsRunning(bool value) { isRunning = value; }
	void SetShootFire(bool value) { shootFire = value; }
	void StartHighSpeed() { highSpeed_start = GetTickCount(); hasHighSpeed = true; }
	void SetIsFirstTimeHighSpeed(bool value) { isFirstTimeHighSpeed = value; }
	void SetHighSpeed(bool value) { hasHighSpeed = value; }
	void SetIsAbleToFly(bool value) { isAbleToFly = value; }
	void SetShoot(int value) { shoot = value; }
	void SetAniShootFire(bool value) { hasAniShootFire = value; }
	void SetIsAppeared(bool value) { isAppeared = value; }
	void Reset();

	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	bool IsJumping() { return isJumping; }
	void SetIsJumping(bool value);
	int GetLevel() { return level; }
	bool CheckStateFlying();
	bool CheckStateFall();
	bool CheckStateFlyingAndFall();
	bool HasTurnBackTail() { return hasTurnBackTail; }
	bool IsStartFlying() { return startFlying; }
	bool GetCheckFall() { return checkFall; }
	DWORD GetIsFlyingStart() { return isFlying_start; }
	bool CheckTimeForFalling() { return  (GetTickCount() - GetIsFlyingStart() < 3000); }
	bool GetIsFirstTimeHighSpeed() { return isFirstTimeHighSpeed; }
	bool GetIsHolding() { return isHolding; }
	bool GetFlagHolding() { return flagHolding; }
	bool GetIsAbleToFly() { return isAbleToFly; }
	bool GetAniShootFire() { return hasAniShootFire; }
	
	// Check condition in Intro Scene
	bool GetIsAbleGreenWalk() { return isGreenAbleWalk; }
	bool GetIsAbleRedWalk() { return isRedAbleWalk; }

	// set true if mario ran 1500 seconds
	bool CheckHighSpeedStart() { return hasHighSpeed && GetTickCount() - highSpeed_start > 1500; }
};