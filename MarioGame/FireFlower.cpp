#include "FireFlower.h"
#include "Collision.h"
#include "Mario.h"
#include "Flower.h"


void CFireFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CFlower*>(obj))
		{
			CFlower* flower = dynamic_cast<CFlower*>(obj);

			// Set isFiring before setting hasFired for flower
			if (isFiring == false)
			{
				if (flower->GetState() == FLOWER_STATE_IDLE && !flower->GetHasFired())
				{
					flower->SetHasFired(true);
					isFiring = true;
					SetPosition(flower->x, flower->y);
					nx = flower->nx;
				}
			}
		}
	}
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
				flagTimeFiring = false;
				isFiring = false;
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
	l = x;
	t = y;
	r = x + FIREFLOWER_BBOX_WIDTH;
	b = y + FIREFLOWER_BBOX_HEIGHT;
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