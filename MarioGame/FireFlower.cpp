#include "FireFlower.h"
#include "Collision.h"
#include "Mario.h"


void CFireFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (isFiring == true)
	{
		SetState(FIRE_FLOWER_STATE_APPEAR);
		if (flagTimeFiring == false)
		{
			timeFirinng_start = GetTickCount();
			flagTimeFiring = true;
		}
		else
		{
			if (GetTickCount() - timeFirinng_start > 3000)
			{
				SetState(FIRE_FLOWER_STATE_DISAPPEAR);
				isFiring = false;
				flagTimeFiring = false;
			}
		}
	}
	else
	{
		SetState(FIRE_FLOWER_STATE_DISAPPEAR);
	}
}
void CFireFlower::Render()
{
	if (state == FIRE_FLOWER_STATE_APPEAR)
	{
		animation_set->at(0)->Render(x, y);
	}
}

void CFireFlower::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}

void CFireFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIRE_FLOWER_STATE_APPEAR:
		vx = nx * 0.05f;
		vy = 0.05f;
		break;
	case FIRE_FLOWER_STATE_DISAPPEAR:
		vx = 0;
		vy = 0;
		break;
	}
}