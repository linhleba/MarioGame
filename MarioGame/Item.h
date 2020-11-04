#pragma once
#include "GameObject.h"

#define ITEM_BBOX_WIDTH  16
#define ITEM_BBOX_HEIGHT 16

class CItem : public CGameObject
{
private:
	bool isAppear = false;
	int typeItem = 0;  // 1:Mushroom, 2:Leaf
	bool isAte = false;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetIsAppear(bool value) { isAppear = value; }
	void SetTypeItem(int value) { typeItem = value; }
	virtual void SetState(int state);
	void SetIsAte(bool value) { value = isAte; }

	bool GetIsAppear() { return isAppear; }
	bool GetIsAte() { return isAte; }
};