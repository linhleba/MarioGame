#include "Pipe.h"

CPipe::CPipe()
{
	this->layerRender = 3;
}

CPipe::CPipe(int type)
{
	typeOfPipe = type;
	this->layerRender = 3;
}

void CPipe::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CPipe::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = x;
	t = y;
	r = x + PIPE_BBOX_WIDTH;
	b = y + PIPE_BBOX_HEIGHT;
}


