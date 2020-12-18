#include "Portal.h"


CPortal::CPortal(double l, double t, double r, double b, int scene_id)
{
	this->scene_id = scene_id;
	x = l;
	y = t;
	width = r - l + 1;
	height = b - t + 1;
}

void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}