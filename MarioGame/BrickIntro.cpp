#include "BrickIntro.h"

void CBrickIntro::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBrickIntro::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = x;
	t = y;
	r = x + BRICK_INTRO_BBOX_WIDTH;
	b = y + BRICK_INTRO_BBOX_HEIGHT;
}