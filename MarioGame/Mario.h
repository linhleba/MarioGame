#pragma once
#include "GameObject.h"
#include "define.h"
#include "Card.h"


class CMario : public CGameObject
{
	vector<int> generalAniBigMario;
	vector<int> generalAniSmallMario;
	vector<int> generalAniFireMario;
	vector<int> generalAniTailMario;
	vector<int> generalAniGreenMario;

	// Set the current index Pipe
	int currentPipeIndex = -1;
	bool isReadyToPiping = false;
	bool isInSecretRoom = false;

	// Check to update if mario is jumping
	//DWORD isJumping_start = 0;
	double prePositionY = 0;


	// Check if Mario is on moving brick or not
	bool isOnMovingBrick = false;

	// Check time to transform for Mario
	bool isTransforming = false;
	bool isLevelUp = false; // false - levelDown, true - levelUp

	DWORD transform_start;
	bool checkTransformStart = false;

	// time to hide fireball mario
	DWORD isEnableFireBall_start;
	bool isEnableFireBall = false;

	// the properties to check if is collision with pipe or not
	bool isDowningPipe = false;
	bool isUppingPipe = false;
	bool isFallDowningPipe = false;

	DWORD timeInDowingPipe_start;
	bool checkTimeInDowingPipe = false;
	DWORD timeInUppingPipe_start;
	bool checkTimeInUppingPipe = false;
	bool secondUppingPipe = false;
	DWORD secondInPipe_start;

	//lock key when end of game or die
	bool lockControl = false;

	// Set to check endgame
	DWORD endGame_start;
	bool  isEndGame = false;
	int card_id = -1;
	

	// get time to die to switch scene
	DWORD timeDie_start;
	bool isTimeDie = false;

	// handle stack for running Mario
	int levelOfStack = 0;
	DWORD timeStackUp_start;
	bool isTimeStackUp = false;

	// define type of mario
	int typeOfMario;
	
	// Check condition in Intro Scene
	bool isAppeared = true;
	bool isGreenAbleWalk = true;
	bool isRedAbleWalk = true;


	int level;
	int untouchable;
	DWORD untouchable_start;

	bool firstTailing = false;
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
	void SetFirstTailing(bool value) { firstTailing = value; }
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
	void SetIsAbleGreenWalk(bool value) { isGreenAbleWalk = value; }
	void SetIsAbleRedWalk(bool value) { isRedAbleWalk = value; }
	void Reset();

	//Count stack for mario
	void SetTheStackUp();
	void SetTheStackDown();
	void SetIsTimeStackUp(bool value);


	virtual void GetBoundingBox(double& left, double& top, double& right, double& bottom);
	bool IsJumping() { return isJumping; }
	void SetIsJumping(bool value);
	int GetLevel() {
		if (this != NULL)
			return level;
		return 1;
	}
	bool CheckStateFlying();
	bool CheckStateFall();
	bool CheckStateFlyingAndFall();
	bool IsFirstTailing() { return firstTailing; }
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
	int GetUntouchable() { return untouchable; }
	
	// Check condition in Intro Scene
	bool GetIsAbleGreenWalk() { return isGreenAbleWalk; }
	bool GetIsAbleRedWalk() { return isRedAbleWalk; }

	// set true if mario ran 1500 seconds
	bool CheckHighSpeedStart() { 
		//return hasHighSpeed && GetTickCount() - highSpeed_start > 1500; 
		return (levelOfStack == 7 && hasHighSpeed);
	}

	// Get stack to update in HUD 
	int GetLevelOfStack() {
		return levelOfStack;
	}

	// Get lock control with Mario
	bool GetLockControl() { return lockControl; }
	// Pipe
	void SetIsDowningPipe(bool value) { isDowningPipe = value; }
	bool GetIsDowningPipe() { return isDowningPipe; }
	void SetIsUppingPipe(bool value) { isUppingPipe = value; }
	bool GetIsUppingPipe() { return isUppingPipe; }

	// Check is transforming or not
	bool GetIsTransforming() { return isTransforming; }
	//Check is end game
	bool GetIsEndGame() { return isEndGame; }
	int GetCardId() { return card_id; }

	// Get previous posY
	double GetPrePosY() { return prePositionY; }

	// Check condition for jump
	bool CheckConditionForJumping()
	{
		return (!this->IsJumping() && ((abs(this->y - this->GetPrePosY()) < 1.0f) || isOnMovingBrick));
	}

	bool GetIsReadyPiping() { return isReadyToPiping; }
	void SetIsReadyPiping(bool value) { isReadyToPiping = value; }
	int GetCurrentPipeIndex() { return currentPipeIndex; }
	void SetIsInSecretRoom(bool value) { isInSecretRoom = value; }
	bool GetIsInSecretRoom() { return isInSecretRoom; }
	void SetIsFallDowningPipe(bool value) { isFallDowningPipe = value; }
};