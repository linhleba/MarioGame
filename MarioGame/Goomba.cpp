#include "Goomba.h"
#include "Utils.h"
#include "Collision.h"
CGoomba::CGoomba(int type)
{
	typeOfGoomba = type;
	if (type == OBJECT_TYPE_GOOMBA)
	{
		SetState(GOOMBA_STATE_WALKING);
	}
	else if (type == OBJECT_TYPE_GOOMBA_FLYING)
	{
		SetState(GOOMBA_STATE_FLYING);
	}
}

void CGoomba::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
	left = x;
	top = y;

	if (state == GOOMBA_STATE_DIE)
	{
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
		right = x + GOOMBA_BBOX_WIDTH;
	}
	else if (state == GOOMBA_STATE_WALKING)
	{
		bottom = y + GOOMBA_BBOX_HEIGHT;
		right = x + GOOMBA_BBOX_WIDTH;
	}
	else if (state == GOOMBA_STATE_FLYING)
	{
		bottom = y + GOOMBA_RED_FLY_BBOX_HEIGHT;
		right = x + GOOMBA_FLYING_BBOX_WIDTH;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	vy += 0.0008 * dt;
	
	if (GetTickCount() - start > 200 && isDie == true)
	{
		SetState(GOOMBA_STATE_DISAPPEAR);
	}
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	if (state == GOOMBA_STATE_FLYING)
	{
		if (!isFLying)
		{
			timeFlying_start = GetTickCount();
			isFLying = true;
		}
		else
		{
			// Set time for Goomba flying
			if (GetTickCount() - timeFlying_start < 100)
			{
				vy = -0.15f;
			}
			// when time is greater than 2000, set isFlying = false to return wal
			if (GetTickCount() - timeFlying_start > 2000)
			{
				isFLying = false;
			}
		}
	}


	if (state != GOOMBA_STATE_DIE && state != GOOMBA_STATE_DISAPPEAR)
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);

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

		collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (ny != 0)
		{
			vy = 0;
		}			
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGoomba*>(e->obj))
			{
				if (e->nx != 0)
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->vx = -goomba->vx;
						this->vx = -this->vx;
					}

				}
			}
			else if (ny == 0 && nx != 0)
			{
				nx = -nx;
				vx = -vx;
			}
		}
		// block object
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CGoomba::Render()
{
	int ani = -1;
		if (state == GOOMBA_STATE_WALKING)
		{
			if (typeOfGoomba == OBJECT_TYPE_GOOMBA)
			{
				ani = GOOMBA_ANI_WALKING;
			}
			else if (typeOfGoomba == OBJECT_TYPE_GOOMBA_FLYING)
			{
				ani = GOOMBA_ANI_RED_WALKING;
			}
		}
		else if (state == GOOMBA_STATE_DIE)
		{
			if (typeOfGoomba == OBJECT_TYPE_GOOMBA)
			{
				ani = GOOMBA_ANI_DIE;
			}
			else if (typeOfGoomba == OBJECT_TYPE_GOOMBA_FLYING)
			{
				ani = GOOMBA_ANI_RED_DIE;
			}
		}
		else if (state == GOOMBA_STATE_FLYING)
		{
			ani = GOOMBA_ANI_FLYING;
		}
		if (ani != -1)
		{
			animation_set->at(ani)->Render(x, y);
		}

}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_DISAPPEAR:
		y = 0;
		x = 0;
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_FLYING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
		
	}
}
