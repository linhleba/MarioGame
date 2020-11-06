#include "Goomba.h"
#include "Utils.h"
#include "Collision.h"
CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	vy += 0.0008 * dt;
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	//if (vx < 0 && x < 386) {
	//	x = 386; vx = -vx;
	//}

	//if (vx > 0 && x > 600) {
	//	x = 600; vx = -vx;
	//}
	if (GetTickCount() - start > 200 && isDie == true)
	{
		SetState(GOOMBA_STATE_DISAPPEAR);
	}
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	if (state != GOOMBA_STATE_DIE && state != GOOMBA_STATE_DISAPPEAR)
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);

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

		collisionHandler->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		// block object
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (ny != 0)
		{
			vy = 0;
		}			
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (ny == 0 && nx != 0)
			{
				nx = -nx;
				vx = -vx;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CGoomba::Render()
{
	if (state == GOOMBA_STATE_WALKING)
	{
		int ani = GOOMBA_ANI_WALKING;
		animation_set->at(ani)->Render(x, y);
	}
	else if (state == GOOMBA_STATE_DIE)
	{
		
		int ani = GOOMBA_ANI_DIE;
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
	}
}
