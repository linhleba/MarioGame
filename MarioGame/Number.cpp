#include "Number.h"

CNumber::CNumber()
{
	SetState(NUMBER_THREE_STATE_DISAPPEAR);
}



void CNumber::Render()
{
	if (state != NUMBER_THREE_STATE_DISAPPEAR)
	{
		animation_set->at(0)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CNumber::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (state == NUMBER_THREE_STATE_APPEAR)
	{
		if (!firstTimeToAppear)
		{
			firstTimeToAppear = true;
		}
		if (!isChangeState)
		{
			timeChangeState_start = GetTickCount();
			isChangeState = true;
		}
		else
		{
			if (GetTickCount() - timeChangeState_start > 600)
			{
				SetState(NUMBER_THREE_STATE_DISAPPEAR);
				isChangeState = false;
			}
		}
	}

	if (firstTimeToAppear)
	{
		if (state == NUMBER_THREE_STATE_DISAPPEAR)
		{
			if (!isChangeState)
			{
				timeChangeState_start = GetTickCount();
				isChangeState = true;
			}
			else
			{
				if (GetTickCount() - timeChangeState_start > 600)
				{
					SetState(NUMBER_THREE_STATE_APPEAR);
					isChangeState = false;;
				}
			}
		}
	}
}

void CNumber::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}

void CNumber::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BACKGROUND_STATE_APPEAR:
		break;
	case BACKGROUND_STATE_DISAPPEAR:
		break;
	}
}
