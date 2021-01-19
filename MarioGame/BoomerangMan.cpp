#include "BoomerangMan.h"
#include "Collision.h"
#include "Game.h"
#include "Boomerang.h"

CBoomerangMan::CBoomerangMan()
{
	SetState(BOOMERANG_MAN_STATE_MOVE_RIGHT);
	this->nx = 1;
}

void CBoomerangMan::Render()
{
	int ani = -1;

	if (state != MARIO_STATE_DIE)
	{
		if (checkThrowingBoomerang)
		{
			if (nx > 0)
				ani = BOOMERANG_MAN_ANI_THROW_BOOMERANG_RIGHT;
			else
			{
				ani = BOOMERANG_MAN_ANI_THROW_BOOMERANG_LEFT;
			}
		}
		else
		{
			if (nx > 0)
				ani = BOOMERANG_MAN_ANI_NORMAL_RIGHT;
			else
			{
				ani = BOOMERANG_MAN_ANI_NORMAL_LEFT;
			}
		}
	}
	else
	{
		if (nx > 0)
			ani = BOOMERANG_MAN_ANI_DIE_RIGHT;
		else
			ani = BOOMERANG_MAN_ANI_DIE_LEFT;
	}
	animation_set->at(ani)->Render(x, y);
}

void CBoomerangMan::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = x;
	t = y;
	r = l + BOOMERANG_MAN_BBOX_WIDTH;
	b = t + BOOMERANG_MAN_BBOX_HEIGHT;
}

void CBoomerangMan::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOOMERANG_MAN_STATE_MOVE_RIGHT:
		vx = 0.03f;
		vy = 0;
		break;
	case BOOMERANG_MAN_STATE_MOVE_LEFT:
		vx = -0.03f;
		vy = 0;
		break;
	case BOOMERANG_MAN_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case BOOMERANG_MAN_STATE_DIE:
		vx = 0;
		break;
	}
}

void CBoomerangMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//DebugOut(L"state boomerang is %d \n", this->GetState());
	// Set gravity for boomerangman
	vy += BOOMERANG_MAN_GRAVITY * dt;

	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (state != BOOMERANG_MAN_STATE_DIE)
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);

	if (state != BOOMERANG_MAN_STATE_DIE)
	{

		if (isChangeState == false)
		{
			isChangeState = true;
			isChangeState_start = GetTickCount();
		}
		else
		{
			if (GetTickCount() - isChangeState_start >= 700)
			{
				SetState(BOOMERANG_MAN_STATE_MOVE_RIGHT);
			}

			if (GetTickCount() - isChangeState_start >= 2000)
			{
				SetState(BOOMERANG_MAN_STATE_IDLE);
			}
			if (GetTickCount() - isChangeState_start >= 2700)
			{
				SetState(BOOMERANG_MAN_STATE_MOVE_LEFT);
			}

			if (GetTickCount() - isChangeState_start >= 4000)
			{
				SetState(BOOMERANG_MAN_STATE_IDLE);
				isChangeState = false;
				//sub_time = 0;
			}
		}

		for (size_t i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT coObject = coObjects->at(i);
			if (dynamic_cast<CBoomerang*>(coObject))
			{
				CBoomerang* boomerang = dynamic_cast<CBoomerang*>(coObject);
				if (!boomerang->GetIsUsing())
				{
					if (this->nx > 0)
						boomerang->nx = 1;
					else
						boomerang->nx = -1;

					boomerang->SetState(BOOMERANG_STATE_FLYING_TOP);
				}
			}
		}
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{

	}
}
