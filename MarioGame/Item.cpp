#include "Item.h"
#include "Utils.h"
#include "Collision.h"
#include "Mario.h"

CItem::CItem()
{
	this->layerRender = 1;
	SetState(ITEM_STATE_DISAPPEAR);
}

CItem::CItem(int type)
{
	this->layerRender = 1;
	typeOfMushRoom = type;
	SetState(ITEM_STATE_DISAPPEAR);
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollisionHandler* collisionHandler = new CCollisionHandler();
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	collisionHandler->CalcPotentialCollisions(coObjects, this, coEvents, dt);
	// state leaf when big mario

	if (state == ITEM_STATE_LEAF_APPEAR)
	{
		SetTimeUpStart();
		SetState(ITEM_STATE_LEAF_UP_MOVING);
	}

	else if (state == ITEM_STATE_LEAF_UP_MOVING)
	{
		y += dy;
		if (GetTickCount() - time_Up_Start > 500)
		{
			SetState(ITEM_STATE_LEAF_DOWN_MOVING);
		}
	}
	else if (state == ITEM_STATE_LEAF_DOWN_MOVING)
	{
		x += dx;
		y += dy;
		if (time_Down_Start == 0)
		{
			SetTimeDownStart();
		}
		else
		{
			if (GetTickCount() - time_Down_Start > 500)
			{
				time_Down_Start = 0;
				vx = -vx;
			}
		}

	}


	// state mushroom when small mario
	if (state == ITEM_STATE_MUSHROOM_APPEAR)
	{
		SetTimeUpStart();
		SetState(ITEM_STATE_MUSHROOM_UP);
		
	}

	if (state == ITEM_STATE_MUSHROOM_UP)
	{
		y += dy;
		if (GetTickCount() - time_Up_Start > 500)
		{
			SetState(ITEM_STATE_MUSHROOM_MOVING);
		}
	}
	if (state == ITEM_STATE_MUSHROOM_MOVING)
	{
		vy += 0.008 * dt;
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
			// block object
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			// Check collision nx to change direction
			if (nx != 0 && ny == 0)
			{
				vx = -vx;
			}

			if (ny != 0)
			{
				vy = 0;
			}
		}
	}

	if (state == ITEM_STATE_FIRE_FLOWER_APPEAR)
	{
		SetTimeUpStart();
		SetState(ITEM_STATE_FIRE_FLOWER_UP);
	}

	if (state == ITEM_STATE_FIRE_FLOWER_UP)
	{
		y += dy;
		if (GetTickCount() - time_Up_Start > 400)
		{
			vy = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CItem::Render()
{
	int ani = -1;
	if (state != ITEM_STATE_DISAPPEAR)
	{
		if (state == ITEM_STATE_MUSHROOM_APPEAR || state == ITEM_STATE_MUSHROOM_UP || state == ITEM_STATE_MUSHROOM_MOVING)
		{
			ani = ITEM_ANI_MUSHROOM;
		}
		else if (state == ITEM_STATE_LEAF_APPEAR)
		{
			ani = ITEM_ANI_LEAF_LEFT;
		}
		else if (state == ITEM_STATE_LEAF_UP_MOVING)
		{
			ani = ITEM_ANI_LEAF_LEFT;
		}

		else if (state == ITEM_STATE_LEAF_DOWN_MOVING)
		{
			if (vx > 0)
			{
				ani = ITEM_ANI_LEAF_RIGHT;
			}
			else
			{
				ani = ITEM_ANI_LEAF_LEFT;
			}
		}
		else if (state == ITEM_STATE_FIRE_FLOWER_APPEAR || state == ITEM_STATE_FIRE_FLOWER_UP)
		{
			ani = ITEM_ANI_FIRE_FLOWER;
		}

		animation_set->at(ani)->Render(x, y);
	}

	//RenderBoundingBox();
}
void CItem::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_MUSHROOM_APPEAR:
		vy = 0;
		vx = 0.04f;
		break;
	case ITEM_STATE_MUSHROOM_UP:
		vy = -0.04f;
		break;
	case ITEM_STATE_MUSHROOM_MOVING:
		break;
	case ITEM_STATE_LEAF_UP_MOVING:
		vy = -0.06f;
		break;
	case ITEM_STATE_LEAF_DOWN_MOVING:
		vx = 0.04f;
		vy = 0.04f;
		break;
	case ITEM_STATE_FIRE_FLOWER_APPEAR:
		vx = 0;
		vy = 0;
		break;
	case ITEM_STATE_FIRE_FLOWER_UP:
		vy = -0.04f;
		break;
	}

}

int CItem::CheckPositionItem()
{
	/*if (x == 241 && y == 18)
	{
		return 1;
	}
	else if (x == 656 && y == 93)
	{
		return 2;
	}
	else if (x == 1472 && y == 82)
	{
		return 3;
	}
	else if (x == 1440 && y == -157)
	{
		return 4;
	}
	else
	{
		return -1;
	}*/
	return 0;
}

int CItem::CheckPositionItemIntro()
{
	if (x == 20 && y == -10)
	{
		return 1;
	}
	else if (x == 145 && y == -10)
	{
		return 2;
	}
	return -1;
}

void CItem::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	if (state != ITEM_STATE_DISAPPEAR)
	{
		l = x;
		t = y;
		r = x + ITEM_BBOX_WIDTH;
		b = y + ITEM_BBOX_HEIGHT;
	}
	else
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}