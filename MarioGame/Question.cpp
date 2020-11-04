#include "Question.h"

void CQuestion::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + QUESTION_BBOX_WIDTH;
	b = y + QUESTION_BBOX_HEIGHT;
}