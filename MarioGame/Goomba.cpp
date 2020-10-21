#include "Goomba.h"
#include "Utils.h"
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

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (vx < 0 && x < 386) {
		x = 386; vx = -vx;
	}

	if (vx > 0 && x > 618) {
		x = 618; vx = -vx;
	}

	if (GetTickCount() - start > 200 && isDie == true)
	{
		state = GOOMBA_STATE_DISAPPEAR;
	}
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
