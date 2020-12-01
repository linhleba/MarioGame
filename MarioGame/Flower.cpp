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
	SetIsShortDistance();
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

	// hoa se ban o ben tren
	if (mario->y < FLOWER_TOP_LIMITATION)
	{
		ny = -1;
	}

	// hoa se ban o phia duoi
	else if (mario->y > FLOWER_TOP_LIMITATION)
	{
		ny = 1;
	}

	// Fixed position
	//posFlower = GetPositionFlower();
	if (state != FLOWER_STATE_DIE)
	{

		// neu vuot qua nguong nay thi hoa se chuyen sang giai doan growing up
		if (y > FLOWER_BOTTOM_LIMITATION)
		{
			SetState(FLOWER_STATE_GROWING_UP);
		}
		else
		{
			// neu hoa nay khac vi tri hoa dang o vi tri thu 3
			if (posFlower != FLOWER_POSITION_RED_UP)
			{
				if (y < FLOWER_TOP_LIMITATION)
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
				if (y < FLOWER_TOP_RED_UP_LIMITATION)
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
	}
}
void CFlower::Render()
{
	posFlower = GetPositionFlower();
	int ani = -1;
	if (state != FLOWER_STATE_DIE)
	{
		if (nx == -1)
		{
			if (ny == 1)
			{
				if (posFlower == FLOWER_POSITION_RED)
				{
					ani = FLOWER_ANI_RED_LEFT_BOTTOM;
				}
				else if (posFlower == FLOWER_POSITION_GREEN)
				{
					ani = FLOWER_ANI_GREEN_LEFT_BOTTOM;
				}
			}
			else
			{
				if (posFlower == FLOWER_POSITION_RED)
				{
					ani = FLOWER_ANI_RED_TOP_LEFT;
				}
				else if (posFlower == FLOWER_POSITION_GREEN)
				{
					ani = FLOWER_ANI_GREEN_TOP_LEFT;
				}
			}
		}
		else if (nx == 1)
		{
			if (ny == 1)
			{
				if (posFlower == FLOWER_POSITION_RED)
				{
					ani = FLOWER_ANI_RED_RIGHT_BOTTOM;
				}
				else if (posFlower == FLOWER_POSITION_GREEN)
				{
					ani = FLOWER_ANI_GREEN_RIGHT_BOTTOM;
				}
			}
			else
			{
				if (posFlower == FLOWER_POSITION_RED)
				{
					ani = FLOWER_ANI_RED_TOP_RIGHT;
				}
				else if (posFlower == FLOWER_POSITION_GREEN)
				{
					ani = FLOWER_ANI_GREEN_TOP_RIGHT;
				}
			}
		}
		if (posFlower == FLOWER_POSITION_RED_UP)
		{
			ani = FLOWER_ANI_RED_TOP;
		}
		animation_set->at(ani)->Render(x, y);
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

void CFlower::SetIsShortDistance()
{
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (abs(mario->x) - this->x <= 160)
	{
		isShortDistance = true;
	}
	else
	{
		isShortDistance = false;
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


void CFlower::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	if (state != FLOWER_STATE_DIE)
	{
		l = x;
		t = y;
		r = x + FLOWER_BBOX_WIDTH;
		b = y + FLOWER_BBOX_HEIGHT;
	}
	else
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}
