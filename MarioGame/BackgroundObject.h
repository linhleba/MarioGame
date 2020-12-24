#pragma once
#include "GameObject.h"


class CBackgroundObject : public CGameObject
{
	int typeOfBackground;
	bool isRender = false;

	DWORD timeRender_start;
	bool isTimeRender = false;
public:
	CBackgroundObject() {};
	CBackgroundObject(int type);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(double& l, double& t, double& r, double& b);
	void SetIsRender(bool value) { isRender = value; }

	bool CheckIsWord()
	{
		return (typeOfBackground == OBJECT_TYPE_FIRST_WORD || typeOfBackground == OBJECT_TYPE_SECOND_WORD
			|| typeOfBackground == OBJECT_TYPE_THIRD_WORD_ITEM);
	}
};