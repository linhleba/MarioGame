#include "HitEffect.h"

CHitEffect::CHitEffect()
{
	SetState(HIT_EFFECT_TAIL_STATE_DISAPPEAR);
	this->layerRender = 9000;
}

void CHitEffect::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = t = r = b = 0;
}

void CHitEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (state == HIT_EFFECT_TAIL_STATE_APPEAR)
	{
		if (timeAppear == false)
		{
			timeAppear_start = GetTickCount();
			timeAppear = true;
		}
		else
		{
			if (GetTickCount() - timeAppear_start > 100)
			{
				SetState(HIT_EFFECT_TAIL_STATE_DISAPPEAR);
				timeAppear = false;
			}
		}
	}
}

void CHitEffect::Render()
{
	if (state != HIT_EFFECT_TAIL_STATE_DISAPPEAR)
	{
		animation_set->at(0)->Render(x, y);
	}
}

void CHitEffect::SetState(int state)
{
	CGameObject::SetState(state);
}
