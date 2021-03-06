#pragma once
#include "GameObject.h"

#define QUESTION_BBOX_WIDTH  16
#define QUESTION_BBOX_HEIGHT 16

class CQuestion : public CGameObject
{
private:

	// check time to get Coin special brick
	int countTimeGetCoin = 0;

	bool isUsed = false;
	bool isMovingUp = true;
	int countTimeUp = 0;
	int typeOfQuestion;
public:
	virtual void Render();
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	CQuestion();
	CQuestion(int type);

	bool CheckQuestionHasMushRoom(vector<LPGAMEOBJECT>* coObjects);
	int GetTypeOfQuestion() { return typeOfQuestion; }
};