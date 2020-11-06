#include "BreakableBrick.h"
#include "PLetter.h"

CBreakableBrick::CBreakableBrick()
{
	SetState(BREAKBRICK_STATE_APPEAR);
}
void CBreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (x == 2032 && y == 102 && state == BREAKBRICK_STATE_DISAPPEAR)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CPLetter*>(obj))
			{
				CPLetter* p = dynamic_cast<CPLetter*>(obj);
				p->SetState(PLETTER_STATE_APPEAR);
				SetState(BREAKBRICK_STATE_BLANK_QUESTION);
			}
		}
	}
}
void CBreakableBrick::Render()
{
	if (state == BREAKBRICK_STATE_APPEAR)
	{
		animation_set->at(BREAKBRICK_ANI_APPEAR)->Render(x, y);
	}
	else if (state == BREAKBRICK_STATE_BLANK_QUESTION)
	{
		animation_set->at(BREAKBRICK_ANI_BLANKQUESTION)->Render(x, y);
	}
	else if (state == BREAKBRICK_STATE_COIN)
	{
		animation_set->at(BREAKBRICK_ANI_COIN)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CBreakableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state != BREAKBRICK_STATE_DISAPPEAR)
	{
		l = x;
		t = y;
		r = x + BBRICK_BBOX_WIDTH;
		b = y + BBRICK_BBOX_HEIGHT;
	}
	else
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}

void CBreakableBrick::SetState(int state)
{
	CGameObject::SetState(state);
}