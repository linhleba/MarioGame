#include "Card.h"
#include "Utils.h"

CCard::CCard()
{
	SetState(CARD_STATE_MUSHROOM);
	vy = 0;
}

void CCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	y += dy;

	if (!isTimeStateChanged)
	{
		timeStateChanged_start = GetTickCount();
		isTimeStateChanged = true;
	}
	else
	{
		if (GetTickCount() - timeStateChanged_start > 250)
		{
			isTimeStateChanged = false;
			switch (state)
			{
			case CARD_STATE_MUSHROOM:
				SetState(CARD_STATE_FIRE_FLOWER);
				break;
			case CARD_STATE_FIRE_FLOWER:
				SetState(CARD_STATE_STAR);
				break;
			case CARD_STATE_STAR:
				SetState(CARD_STATE_MUSHROOM);
				break;
			default:
				break;
			}
		}
	}
}

void CCard::Render()
{
	int ani = -1;
	switch (state)
	{
	case CARD_STATE_MUSHROOM:
		ani = CARD_ANI_MUSHROOM_IDLE;
		break;
	case CARD_STATE_FIRE_FLOWER:
		ani = CARD_ANI_FLOWER_IDLE;
		break;
	case CARD_STATE_STAR:
		ani = CARD_ANI_STAR_IDLE;
		break;
	case CARD_STATE_MUSHROOM_MOVING:
		ani = CARD_ANI_MUSHROOM_UP;
		break;
	case CARD_STATE_FIRE_FLOWER_MOVING:
		ani = CARD_ANI_FLOWER_UP;
		break;
	case CARD_STATE_STAR_MOVING:
		ani = CARD_ANI_STAR_UP;
		break;

	}
	if (ani != -1)
	{
		animation_set->at(ani)->Render(x, y);
	}
	
}

void CCard::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CARD_STATE_MUSHROOM:
		break;
	case CARD_STATE_FIRE_FLOWER:
		break;
	case CARD_STATE_STAR:
		break;
	case CARD_STATE_MUSHROOM_MOVING:
		vy = CARD_SPEED_OF_MOVING;
		break;
	case CARD_STATE_FIRE_FLOWER_MOVING:
		vy = CARD_SPEED_OF_MOVING;
		break;
	case CARD_STATE_STAR_MOVING:
		vy = CARD_SPEED_OF_MOVING;
		break;
	}
}

void CCard::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	if (state != CARD_STATE_FIRE_FLOWER_MOVING && state != CARD_STATE_MUSHROOM_MOVING && state != CARD_STATE_STAR_MOVING)
	{
		l = x;
		t = y;
		r = x + CARD_BBOX_WIDTH;
		b = y + CARD_BBOX_HEIGHT;
	}
	else
	{
		l = t = r = b = 0;
	}
}
