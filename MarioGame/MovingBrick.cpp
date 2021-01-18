#include "MovingBrick.h"

CMovingBrick::CMovingBrick()
{
	SetState(MOVING_BRICK_STATE_MOVING);
	this->layerRender = 4;
}

void CMovingBrick::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CMovingBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MOVING_BRICK_STATE_MOVING:
		vx = -MOVING_BRICK_SPEED_MOVING;
		vy = 0;
		break;
	case MOVING_BRICK_STATE_FALLING:
		vx = 0;
		vy = MOVING_BRICK_SPEED_FALLING;
		break;
	}
}

void CMovingBrick::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = x;
	t = y;
	r = x + BBOX_MOVING_BRICK_WIDTH;
	b = y + BBOX_MOVING_BRICK_HEIGHT;
	
}

void CMovingBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
}
