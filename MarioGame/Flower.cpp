#include "Flower.h"
#include "FireFlower.h"
#include "Utils.h"
#include "Collision.h"
#include "Mario.h"
#include "PlayScence.h"
CFlower::CFlower()
{
	SetState(FLOWER_STATE_GROWING_UP);
}

void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	y += dy;
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->x < this->x)
	{
		nx = -1;
	}
	else if (mario->x > this->x)
	{
		nx = 1;
	}

	// Fixed position
	if (y > 118)
	{
		SetState(FLOWER_STATE_GROWING_UP);
	}
	else if (y < 70)
	{
		if (isFirstFiring == false)
		{
			isFirstFiring = true;
			timeFiring_start = GetTickCount();
		}
		if (isFirstFiring && GetTickCount() - timeFiring_start > 3000)
		{
			SetState(FLOWER_STATE_GROWING_DOWN);
			isFirstFiring = false;
		}
		else
		{
			SetState(FLOWER_STATE_IDLE);
		}
	}

	// Update fire flower when flower is idle
	if (state == FLOWER_STATE_IDLE)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CFireFlower*>(obj))
			{
				CFireFlower *fireFlower = dynamic_cast<CFireFlower*>(obj);
				if (fireFlower->GetIsFiring() == false)
				{
					fireFlower->SetIsFiring(true);
					fireFlower->SetPosition(this->x, this->y);
					fireFlower->nx = nx;
				}
			}
		}
	}
}
void CFlower::Render()
{
	if (nx == -1)
	{
		animation_set->at(FLOWER_ANI_LEFT_BOTTOM)->Render(x, y);
	}
	else if (nx == 1)
	{
		animation_set->at(FLOWER_ANI_RIGHT_BOTTOM)->Render(x, y);
	}
	
}
void CFlower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOWER_STATE_GROWING_UP:
		vy = -0.03f;
		break;
	case FLOWER_STATE_GROWING_DOWN:
		vy = 0.03f;
		break;
	case FLOWER_STATE_IDLE:
		vy = 0;
		break;
	}
}


void CFlower::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}
