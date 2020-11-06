#include "Flower.h"
#include "Utils.h"
#include "Collision.h"
#include "Mario.h"
#include "PlayScence.h"

void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->x < this->x)
	{
		SetState(FLOWER_STATE_LEFT_BOTTOM);
	}
	else if (mario->x > this->x)
	{
		SetState(FLOWER_STATE_RIGHT_BOTTOM);
	}
	
}
void CFlower::Render()
{
	if (state == FLOWER_STATE_LEFT_BOTTOM)
	{
		animation_set->at(FLOWER_ANI_LEFT_BOTTOM)->Render(x, y);
	}
	else if (state == FLOWER_STATE_RIGHT_BOTTOM)
	{
		animation_set->at(FLOWER_ANI_RIGHT_BOTTOM)->Render(x, y);
	}
	
}
void CFlower::SetState(int state)
{
	CGameObject::SetState(state);
}


void CFlower::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}
