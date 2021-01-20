#include "Boomerang.h"
#include "Collision.h"
#include "BoomerangMan.h"

CBoomerang::CBoomerang()
{
	SetState(BOOMERANG_STATE_DISAPPEAR);
	this->layerRender = 200;
}

CBoomerang::CBoomerang(int type)
{
	typeOfBoomerang = type;
	this->layerRender = 200;
	SetState(BOOMERANG_STATE_DISAPPEAR);
}

void CBoomerang::Render()
{
	int ani = -1;

	if (state != BOOMERANG_STATE_DISAPPEAR)
	{
		if (nx > 0)
			ani = BOOMERANG_ANI_FLYING_RIGHT;
		else
			ani = BOOMERANG_ANI_FLYING_LEFT;
	}
	if (ani != -1)
	{
		animation_set->at(ani)->Render(x, y);
	}
}

void CBoomerang::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	if (state != BOOMERANG_STATE_DISAPPEAR)
	{
		l = x;
		t = y;
		r = x + BOOMERANG_BBOX_WIDTH;
		b = y + BOOMERANG_BBOX_HEIGHT;
	}
	else
	{
		l = t = r = b = 0;
	}
}

void CBoomerang::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOOMERANG_STATE_DISAPPEAR:
		vx = 0;
		vy = 0;
		break;
	case BOOMERANG_STATE_FLYING_TOP:
		break;
	case BOOMERANG_STATE_FLYING_RIGHT:
		break;
	case BOOMERANG_STATE_FLYING_BOTTOM:
		break;
	case BOOMERANG_STATE_FLYING_LEFT:
		break;
	default:
		break;
	}
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	// Set to check diff time
	if (preTime_start == 0)
	{
		preTime_start = GetTickCount();
	}
	else
	{
		if (GetTickCount() - preTime_start <= 50)
		{
			preTime_start = GetTickCount();
		}
		else
		{
			diff_time = GetTickCount() - preTime_start;
			preTime_start = GetTickCount();
		}
	}
	
	if (state == BOOMERANG_STATE_FLYING_TOP)
	{
		if (GetTickCount() - isChangeState_start >= 500)
		{
			SetState(BOOMERANG_STATE_FLYING_RIGHT);
		}
		else
		{
			if (GetTickCount() - isChangeState_start >= 50)
			{
				vx = 0.1f * nx;
				vy += -0.00006f * dt;
			}
			else
			{
				vx = vy = 0;
			}
		}
		if (GetTickCount() - isChangeState_start >= 250)
		{
			// begin to calc the collision
			isAllowForCollision = true;
		}
	}
	else if (state == BOOMERANG_STATE_FLYING_RIGHT)
	{
		if (GetTickCount() - isChangeState_start >= 1200)
		{
			SetState(BOOMERANG_STATE_FLYING_BOTTOM);
		}
		else
		{
			vx = 0.1f * nx;
			vy += 0.00015f * dt;
		}
	}
	else if (state == BOOMERANG_STATE_FLYING_BOTTOM)
	{
		if (GetTickCount() - isChangeState_start >= 1600)
		{
			SetState(BOOMERANG_STATE_FLYING_LEFT);
		}
		else
		{
			vx = -0.1f * nx;
			vy += 0.00006f * dt;
		}
	}
	else if (state == BOOMERANG_STATE_FLYING_LEFT)
	{
		if (GetTickCount() - isChangeState_start >= 4000)
		{
			SetState(BOOMERANG_STATE_DISAPPEAR);
			isChangeStart = false;
			isUsing = false;
		}
		else
		{
			vx = -0.1f * nx;
			vy = 0;
		}
	}


	// === HANDLE COLLISION ===
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (state != BOOMERANG_STATE_DISAPPEAR)
	{
		if (isAllowForCollision)
			collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		double min_tx, min_ty, nx = 0, ny;
		double rdx = 0;
		double rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


		// block every object first!
		//x += min_tx * dx + nx * 0.4f;
		//y += min_ty * dy + ny * 0.4f;

		for (size_t i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBoomerangMan*>(e->obj))
			{
				CBoomerangMan* boomerangMan = dynamic_cast<CBoomerangMan*>(e->obj);
				this->isUsing = false;
				SetState(BOOMERANG_STATE_DISAPPEAR);
			}
		}
	}

}

