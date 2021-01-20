#include "Pipe.h"

CPipe::CPipe(int type, int id)
{
	this->layerRender = 100;
	typeOfPipe = type;
	idPipe = id;
}

CPipe::CPipe()
{
	this->layerRender = 100;
}

CPipe::CPipe(int type)
{
	typeOfPipe = type;
	this->layerRender = 100;
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


