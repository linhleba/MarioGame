#include "BackgroundObject.h"

void CBackgroundObject::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBackgroundObject::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}