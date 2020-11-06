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
	posFlower = GetPositionFlower();
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
	//posFlower = GetPositionFlower();
	if (y > 118)
	{
		SetState(FLOWER_STATE_GROWING_UP);
	}
	else
	{
		if (posFlower != 3)
		{
			if (y < 70)
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
		}
		else
		{
			if (y < 86)
			{
				SetState(FLOWER_STATE_GROWING_DOWN);
			}
		}
	}

	// Update fire flower when flower is idle
	if (state != FLOWER_STATE_IDLE)
	{
		hasFired = false;
	}

	// Handle Collision

	//CCollisionHandler* collisionHandler = new CCollisionHandler();
	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;
	//collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	//if (coEvents.size() != 0)
	//{
	//	float min_tx, min_ty, nx = 0, ny;
	//	float rdx = 0;
	//	float rdy = 0;

	//	// TODO: This is a very ugly designed function!!!!
	//	collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
	//}
}
void CFlower::Render()
{
	posFlower = GetPositionFlower();
	int ani = -1;
	if (nx == -1)
	{
		if (posFlower == 1)
		{
			ani = FLOWER_ANI_RED_LEFT_BOTTOM;
		}
		else if (posFlower == 2)
		{
			ani = FLOWER_ANI_GREEN_LEFT_BOTTOM;
		}
	}
	else if (nx == 1)
	{
		if (posFlower == 1)
		{
			ani = FLOWER_ANI_RED_RIGHT_BOTTOM;
		}
		else if (posFlower == 2)
		{
			ani = FLOWER_ANI_GREEN_RIGHT_BOTTOM;
		}
	}
	if (posFlower == 3)
	{
		ani = FLOWER_ANI_RED_TOP;
	}
	animation_set->at(ani)->Render(x, y);

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

int CFlower::GetPositionFlower()
{
	if (350 < this->x && this->x < 370)
		return 1;
	else if (1850 < this->x && this->x < 1880)
		return 2;
	else if (1790 < this->x && this->x < 1810)
		return 3;
	else
		return -1;
}


void CFlower::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FLOWER_BBOX_WIDTH;
	b = y + FLOWER_BBOX_HEIGHT;
}
