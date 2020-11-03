#include "Koopas.h"
#include "Collision.h"
#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"

CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);

}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_DIE)
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	else if (state == KOOPAS_STATE_RUNNING_SHELL_RIGHT || state == KOOPAS_STATE_RUNNING_SHELL_LEFT)
		bottom = y + KOOPAS_BBOX_HEIGHT_SHELL;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	//if (state != KOOPAS_STATE_DIE)
	{
		vy += 0.0008 * dt;
	}
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	if (state != KOOPAS_STATE_DIE_FALL)
	collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	

	if (x < 0 && vx < 0) {
			x = 0; vx = -vx;
	}
	

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (ny != 0)
		{
			vy = 0;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			/*if (dynamic_cast<CMario*>(e->obj) || dynamic_cast<CGoomba*>(e->obj) || dynamic_cast<CKoopas*>(e->obj))
			{
				nx = 0;
			}
			else*/ if (ny == 0 && nx != 0)
			{
				nx = -nx;
				vx = -vx;
			}
		}
		// block object
		x += min_tx * dx + nx * 0.4f;

	}
	if (state == KOOPAS_STATE_RUNNING_SHELL_LEFT || state == KOOPAS_STATE_RUNNING_SHELL_RIGHT)
	{
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				goomba->SetState(GOOMBA_STATE_DIE);
				goomba->SetGoombaDie();
				goomba->SetTickCount();
			}
			if (dynamic_cast<CKoopas*>(e->obj))
			{
				e->obj->SetState(KOOPAS_STATE_DIE_FALL);
				//this->SetState(KOOPAS_STATE_DIE_FALL);
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_DIE_FALL) {
		ani = KOOPAS_ANI_DIE;
		/*	DWORD timeRenew = GetTickCount();
			if (timeRenew > 1000)
			{
				ani = KOOPAS_ANI_RENEW;
			}*/
	}
	else if (state == KOOPAS_STATE_RUNNING_SHELL_RIGHT || state == KOOPAS_STATE_RUNNING_SHELL_LEFT)
	{
		ani = KOOPAS_ANI_RUNNING_SHELL;
	}
	else if (vx > 0) ani = KOOPAS_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = KOOPAS_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE - 1;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_RUNNING_SHELL_RIGHT:
		//y = 130.0f;
		vx = 0.2f;
		vy = 0;
		break;
	case KOOPAS_STATE_RUNNING_SHELL_LEFT:
		vx = -0.2f;
		vy = 0;
		break;
	case KOOPAS_STATE_DIE_FALL: 
		vy = -0.1f;
		vx = 0;
		break;
	}

}