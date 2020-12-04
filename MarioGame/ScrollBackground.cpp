#include "ScrollBackground.h"
#include "Collision.h"
#include "define.h"

CScrollBackground::CScrollBackground()
{
	SetState(SCROLL_BACKGROUND_STATE_IDLE);
}


void CScrollBackground::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
	left = top = right = bottom = 0;
}

void CScrollBackground::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	
	x += dx;
	y += dy;

	// Set time to scroll up background
	if (!isScrollStart)
	{
		time_ScrollStart = GetTickCount();
		isScrollStart = true;
	}
	else if (GetTickCount() - time_ScrollStart > 1000)
	{
		SetState(SCROLL_BACKGROUND_STATE_MOVING_UP);
	}
}

void CScrollBackground::Render()
{
	animation_set->at(SCROLL_BACKGROUNND_ANI)->Render(x, y);

	//RenderBoundingBox();
}

void CScrollBackground::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SCROLL_BACKGROUND_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case SCROLL_BACKGROUND_STATE_MOVING_UP:
		vy = -0.1f;
		break;
	}
}




