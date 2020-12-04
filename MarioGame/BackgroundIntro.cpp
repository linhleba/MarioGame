#include "BackgroundIntro.h"
#include "Utils.h"
#include "Collision.h"



CBackgroundIntro::CBackgroundIntro(int type)
{
	typeOfBackground = type;
	SetState(BACKGROUND_STATE_DISAPPEAR);
}

void CBackgroundIntro::Render()
{
	int ani = -1;
	if (state != BACKGROUND_STATE_DISAPPEAR)
	{
		if (typeOfBackground == OBJECT_TYPE_FIRST_BACKGROUND)
		{
			ani = FIRST_BACKGROUND_ANI;
		
		}
		else if (typeOfBackground == OBJECT_TYPE_SECOND_BACKGROUND)
		{
			ani = SECOND_BACKGROUND_ANI;
		}
		else if (typeOfBackground == OBJECT_TYPE_FINAL_BACKGROUND)
		{
			ani = FINAL_BACKGROUND_ANI;

		}

		animation_set->at(ani)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CBackgroundIntro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CGameObject::Update(dt, coObjects);
	this->y += dy;

	//collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	// No collision occured, proceed normally
	
	this->x += dx;
	if (typeOfBackground == OBJECT_TYPE_FIRST_BACKGROUND)
	{
		SetState(BACKGROUND_STATE_APPEAR);
	}

	else if (typeOfBackground == OBJECT_TYPE_SECOND_BACKGROUND)
	{
		if (state == BACKGROUND_STATE_APPEAR)
		{
			if (!isTimeBackgroundDown)
			{
				timeBackgroundDown_start = GetTickCount();
				isTimeBackgroundDown = true;
			}
		}
		if (isTimeBackgroundDown)
		{
			if (GetTickCount() - timeBackgroundDown_start >= 500)
			{
				SetState(BACKGROUND_STATE_APPEAR);
			}
			else
			{
				SetState(BACKGROUND_STATE_MOVING_DOWN);
			}
			if (GetTickCount() - isTimeBackgroundDown >= 700)
			{
				//SetState(BACKGROUND_STATE_VIBRATING);
			}
			if (GetTickCount() - timeBackgroundDown_start >= 1400)
			{
				SetState(BACKGROUND_STATE_APPEAR);
			}

			//SetState(BACKGROUND_STATE_MOVING_DOWN);
		}

	}
	if (state == BACKGROUND_STATE_VIBRATING)
	{
		//this->vy = -vy * 0.2f;
	}
}

void CBackgroundIntro::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}

void CBackgroundIntro::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BACKGROUND_STATE_APPEAR:
		vx = 0;
		vy = 0;
		break;
	case BACKGROUND_STATE_DISAPPEAR:
		break;
	case BACKGROUND_STATE_MOVING_DOWN:
		vy = 0.1f;
		break;

	}
}
