#include "BackgroundObject.h"

CBackgroundObject::CBackgroundObject(int type)
{
	typeOfBackground = type;
}

void CBackgroundObject::Render()
{
	if (typeOfBackground != OBJECT_TYPE_BUSH_HIDING_MARIO)
	{
		animation_set->at(0)->Render(x, y);
	}
	else if (isRender)
	{
		animation_set->at(0)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CBackgroundObject::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}