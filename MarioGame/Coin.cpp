#include "Coin.h"

CCoin::CCoin()
{
	this->layerRender = 2;
}

void CCoin::Render()
{
	if (state != COIN_STATE_DISAPPEAR)
	{
		animation_set->at(0)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	if (state != COIN_STATE_DISAPPEAR)
	{
		l = x;
		t = y;
		r = x + COIN_BBOX_WIDTH;
		b = y + COIN_BBOX_HEIGHT;
	}
	else
	{
		l = t = r = b = 0;
	}
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_STATE_DISAPPEAR:
	/*	y = 0;
		x = 0;*/
		break;
	}
}