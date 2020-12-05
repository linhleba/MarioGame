#include "Star.h"
#include "Collision.h"

CStar::CStar()
{
	SetState(STAR_STATE_DISAPPEAR);
}



void CStar::Render()
{
	if (state != STAR_STATE_DISAPPEAR)
	{
		animation_set->at(0)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (state != STAR_STATE_DISAPPEAR)
	{
		vy += 0.0008 * dt;
	}
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	if (state != STAR_STATE_DISAPPEAR)
	{
		collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
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

void CStar::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = x;
	t = y;
	if (state == STAR_STATE_DISAPPEAR)
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
	else if (state == STAR_STATE_APPEAR)
	{
		r = l + STAR_BBOX_WIDTH;
		b = t + STAR_BBOX_HEIGHT;
	}
}

void CStar::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STAR_STATE_APPEAR:
		break;
	case STAR_STATE_DISAPPEAR:
		vx = 0;
		vy = 0;
		break;
	}
}
