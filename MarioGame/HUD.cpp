#include "HUD.h"
#include "Game.h"
#include "define.h"



CHUD::CHUD(int type)
{
	typeOfHud = type;
}

void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
CGameObject:Update(dt, coObjects);
}

void CHUD::Render()
{
	
}

void CHUD::GetBoundingBox(double& l, double& t, double& r, double& b)
{
	l = t = r = b = 0;
}

void CHUD::SetState(int state)
{
	CGameObject::SetState(state);
}
